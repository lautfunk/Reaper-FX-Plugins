-- LautFunk MIDI Chaos Engine / Host Parameter Bridge v1.0
-- REAPER ReaScript (Lua); GUI is optional and independent of the JSFX editor.
-- Maps up to 16 HOST lanes (type 7) to arbitrary REAPER FX parameters.
-- No external dependencies; per-project mapping is saved in project extension state.

local SECTION = 'LautFunkChaosBridgeV1'
local SEGMENT = 'LautFunk_Chaos_Engine'
local group_id = 1
local selected_track
local targets = {}
local last_values = {}
local cached_types = {}
local cached_enabled = {}
local click_was_down = false
local last_heartbeat, last_seen = -1, 0
local running = true
local last_poll = 0

local function valid_track(tr)
  return tr and reaper.ValidatePtr2(0, tr, 'MediaTrack*')
end
local function guid_of(tr)
  return valid_track(tr) and reaper.GetTrackGUID(tr) or ''
end
local function find_track(guid)
  if not guid or guid == '' then return nil end
  local n = reaper.CountTracks(0)
  for i=0,n-1 do
    local tr = reaper.GetTrack(0,i)
    if reaper.GetTrackGUID(tr) == guid then return tr end
  end
  return nil
end
local function fx_guid(tr, fx)
  if not valid_track(tr) or fx < 0 then return '' end
  return reaper.TrackFX_GetFXGUID(tr, fx) or ''
end
local function resolve_fx(tr, guid)
  if not valid_track(tr) or guid == '' then return -1 end
  for i=0,reaper.TrackFX_GetCount(tr)-1 do
    if fx_guid(tr, i) == guid then return i end
  end
  return -1
end
local function fx_name(tr, idx)
  if not valid_track(tr) or idx < 0 then return '<unassigned>' end
  local ok, s = reaper.TrackFX_GetFXName(tr, idx, '')
  if not ok then return '<missing FX>' end
  return s:gsub('^VST3i?: ', ''):gsub('^JS: ', '')
end
local function param_name(tr, fx, idx)
  if not valid_track(tr) or fx < 0 or idx < 0 then return '<unassigned>' end
  local ok, s = reaper.TrackFX_GetParamName(tr, fx, idx, '')
  return ok and s or '<missing param>'
end
local function save()
  reaper.SetProjExtState(0, SECTION, 'group', tostring(group_id))
  reaper.SetProjExtState(0, SECTION, 'track', guid_of(selected_track))
  for lane=1,16 do
    local item=targets[lane] or {fx='',param=-1}
    reaper.SetProjExtState(0, SECTION, 'fx'..lane, item.fx or '')
    reaper.SetProjExtState(0, SECTION, 'param'..lane, tostring(item.param or -1))
  end
end
local function getstate(key)
  local ok,val=reaper.GetProjExtState(0, SECTION, key)
  if ok==1 then return val end
  return nil
end
local function load()
  group_id=math.max(1,math.min(16,tonumber(getstate('group')) or 1))
  selected_track=find_track(getstate('track')) or reaper.GetSelectedTrack(0,0)
  for l=1,16 do
    targets[l]={fx=getstate('fx'..l) or '',param=tonumber(getstate('param'..l)) or -1}
    last_values[l]=-1
  end
end
local function set_target_track(tr)
  if valid_track(tr) then selected_track=tr;save() end
end
local function choose_fx(lane)
  if not valid_track(selected_track) then return end
  local opts={'<no assignment>'}
  for i=0,reaper.TrackFX_GetCount(selected_track)-1 do
    opts[#opts+1]=fx_name(selected_track,i):gsub('[|!#<>]',' ')
  end
  local menu=gfx.showmenu(table.concat(opts,'|'))
  if menu==0 then return end
  if menu==1 then targets[lane]={fx='',param=-1}
  else targets[lane]={fx=fx_guid(selected_track,menu-2),param=-1} end
  last_values[lane]=-1
  save()
end
local function choose_param(lane)
  if not valid_track(selected_track) then return end
  local tr=targets[lane]
  local fx=resolve_fx(selected_track,tr.fx)
  if fx<0 then return end
  local opts={'<no assignment>'}
  local n=reaper.TrackFX_GetNumParams(selected_track,fx)
  for i=0,n-1 do
    opts[#opts+1]=string.format('%d: %s',i+1,param_name(selected_track,fx,i)):gsub('[|!#<>]',' ')
  end
  local menu=gfx.showmenu(table.concat(opts,'|'))
  if menu==0 then return end
  targets[lane].param=menu-2
  last_values[lane]=-1
  save()
end
local function find_chaos(tr)
  if not valid_track(tr) then return -1 end
  for i=0,reaper.TrackFX_GetCount(tr)-1 do
    if fx_name(tr,i):find('MIDI Chaos Engine',1,true) then return i end
  end
  return -1
end
local function auto_fartsynth()
  if not valid_track(selected_track) then return false,'Select a track first' end
  local synth=-1
  for i=0,reaper.TrackFX_GetCount(selected_track)-1 do
    if fx_name(selected_track,i):find('FartSynth',1,true) then synth=i;break end
  end
  if synth<0 then return false,'FartSynth was not found on the selected track' end
  local chaos=find_chaos(selected_track)
  if chaos<0 then return false,'Chaos Engine was not found on the selected track' end
  local guid=fx_guid(selected_track,synth)
  local n=reaper.TrackFX_GetNumParams(selected_track,synth)
  for lane=1,16 do
    targets[lane]={fx=guid,param=lane<=n and lane-1 or -1}
    last_values[lane]=-1
    -- JSFX host parameters are 0-based. Type 7 = HOST (Lua bridge).
    reaper.TrackFX_SetParam(selected_track,chaos,(83+(lane-1)*7)-1,1)
    reaper.TrackFX_SetParam(selected_track,chaos,(84+(lane-1)*7)-1,7)
  end
  save()
  return true,'FartSynth mapped: 16 host parameter lanes'
end
local function poll()
  local base=group_id*1024
  local magic=reaper.gmem_read(base)
  if magic~=314159 then return end
  local h=reaper.gmem_read(base+1)
  if h~=last_heartbeat then
    last_heartbeat=h
    last_seen=reaper.time_precise()
  end
  if reaper.time_precise()-last_seen>2.5 then return end
  if not valid_track(selected_track) then return end
  for l=1,16 do
    cached_enabled[l]=reaper.gmem_read(base+18+l-1)>0.5
    cached_types[l]=reaper.gmem_read(base+34+l-1)
    if cached_enabled[l] and math.floor(cached_types[l]+.5)==7 then
      local target=targets[l]
      if target and target.param>=0 then
        local fx=resolve_fx(selected_track,target.fx)
        if fx>=0 and target.param<reaper.TrackFX_GetNumParams(selected_track,fx) then
          local v=math.max(0,math.min(1,reaper.gmem_read(base+2+l-1)))
          if math.abs(v-last_values[l])>.0025 then
            reaper.TrackFX_SetParamNormalized(selected_track,fx,target.param,v)
            last_values[l]=v
          end
        end
      end
    end
  end
end
local function color(r,g,b,a) gfx.set(r,g,b,a or 1) end
local function rect(x,y,w,h,r,g,b)
  color(r,g,b);gfx.rect(x,y,w,h,1)
end
local function txt(x,y,s,size,r,g,b)
  gfx.setfont(1,'Arial',size or 13)
  color(r or .85,g or .9,b or .94)
  gfx.x=x;gfx.y=y;gfx.drawstr(tostring(s))
end
local function inrect(x,y,w,h)
  return gfx.mouse_x>=x and gfx.mouse_x<x+w and gfx.mouse_y>=y and gfx.mouse_y<y+h
end
local function button(x,y,w,h,label,active,clicked)
  local hover=inrect(x,y,w,h)
  rect(x,y,w,h,active and .10 or (hover and .11 or .07), active and .37 or (hover and .21 or .13),active and .39 or (hover and .28 or .19))
  rect(x,y,3,h,.18,.91,.77)
  txt(x+10,y+7,label,13)
  return clicked and hover
end
local message='Configure the Host lanes (type=7) in the Chaos Engine.'
local function draw()
  local w,h=gfx.w,gfx.h
  local mouse_down=(gfx.mouse_cap&1)~=0
  local clicked=mouse_down and not click_was_down
  click_was_down=mouse_down
  rect(0,0,w,h,.025,.034,.054)
  txt(20,13,'LautFunk  /  CHAOS PARAMETER BRIDGE',22,.18,.94,.83)
  txt(20,46,'Separate Lua companion - JSFX has its own custom GUI',11,.62,.74,.80)
  local trname='<select a track>'
  if valid_track(selected_track) then
    local _,name=reaper.GetTrackName(selected_track,'')
    trname=name
  end
  txt(20,85,'TRACK: '..trname,12,.75,.85,.91)
  if button(w-385,77,155,32,'USE SELECTED TRACK',false,clicked) then
    local tr=reaper.GetSelectedTrack(0,0)
    if tr then set_target_track(tr);message='Track selected' end
  end
  if button(w-217,77,64,32,'ID -',false,clicked) then group_id=math.max(1,group_id-1);save() end
  if button(w-148,77,64,32,'ID +',false,clicked) then group_id=math.min(16,group_id+1);save() end
  txt(w-78,85,tostring(group_id),15,.18,.92,.77)
  if button(20,123,210,36,'AUTO-MAP FARTSYNTH',false,clicked) then
    local ok;ok,message=auto_fartsynth()
  end
  txt(248,130,'WARNING: Auto-map replaces the 16 engine modulation lane mappings.',11,.76,.65,.65)
  rect(20,176,w-40,27,.09,.15,.20)
  txt(33,182,'LANE',11);txt(108,182,'TARGET FX',11);txt(w*.56,182,'PARAMETER',11);txt(w-90,182,'STATUS',11)
  for lane=1,16 do
    local y=208+(lane-1)*31
    if lane%2==0 then rect(20,y,w-40,30,.055,.08,.12) end
    txt(36,y+6,string.format('%02d',lane),12,.18,.91,.77)
    local t=targets[lane]
    local fx=resolve_fx(selected_track,t.fx)
    local label=fx_name(selected_track,fx)
    if #label>32 then label=label:sub(1,29)..'...' end
    if button(96,y+2,w*.44-104,27,label,false,clicked) then choose_fx(lane) end
    local plabel=param_name(selected_track,fx,t.param)
    if #plabel>26 then plabel=plabel:sub(1,23)..'...' end
    if button(w*.55,y+2,w*.34-15,27,plabel,false,clicked) then choose_param(lane) end
    local active=cached_enabled[lane] and cached_types[lane]==7
    txt(w-88,y+7,active and 'HOST' or '---',11,active and .18 or .52,active and .9 or .65,active and .76 or .7)
  end
  local signal=(reaper.time_precise()-last_seen)<2.5
  txt(25,h-59,message,11,.68,.77,.82)
  txt(25,h-35,signal and 'CONNECTED TO JSFX' or 'WAITING FOR JSFX / PLAYBACK',11,signal and .18 or .99,signal and .91 or .62,.73)
  txt(w-210,h-35,'ESC TO CLOSE',11,.55,.7,.78)
  gfx.update()
end

reaper.gmem_attach(SEGMENT)
load()
gfx.init('LautFunk Chaos Bridge v1.0',1030,775,0,130,100)
local function loop()
  if gfx.getchar()<0 then save();return end
  if reaper.time_precise()-last_poll>.030 then
    poll()
    last_poll=reaper.time_precise()
  end
  draw()
  reaper.defer(loop)
end
loop()