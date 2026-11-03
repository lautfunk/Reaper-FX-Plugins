-- SPDX-License-Identifier: MIT
-- Copyright (c) 2026 LautFunk contributors
-- See LICENSE in the repository root for permissions and warranty disclaimer.
-- LautFunk SoftGuard - Renderziele fuer bestehendes REAPER-Projekt
-- Sets only the current project's render normalization and true-peak brickwall.
-- Does not start a render, change output path/format, or touch the source tracks.

local r = reaper
local ok, user = r.GetUserInputs("LautFunk - Render-Ziele", 2,
  "Integrated LUFS (-),True Peak dBTP (-)", "-14,-1.0")
if not ok then return end
local target_text, peak_text = user:match("^%s*([^,]+)%s*,%s*([^,]+)%s*$")
local loudness = target_text and tonumber(target_text)
local tp = peak_text and tonumber(peak_text)
if not loudness or not tp or loudness < -40 or loudness > -6 or tp < -12 or tp > -0.1 then
  r.MB("Bitte gueltige Werte angeben: LUFS -40 bis -6, True Peak -12 bis -0.1 dBTP.\nBeispiel: -14,-1.0", "LautFunk - Ungueltige Eingabe", 0)
  return
end

local proj = 0
local norm_target = 10 ^ (loudness / 20)
local truepeak_target = 10 ^ (tp / 20)
-- 1 = normalization on, LUFS-I mode (bits 2/4/8 cleared)
-- 64 = brickwall limit on, 128 = true peak limiting (rather than sample peak).
local flags = 1 + 64 + 128
r.Undo_BeginBlock()
r.GetSetProjectInfo(proj, "RENDER_NORMALIZE", flags, true)
r.GetSetProjectInfo(proj, "RENDER_NORMALIZE_TARGET", norm_target, true)
r.GetSetProjectInfo(proj, "RENDER_BRICKWALL", truepeak_target, true)
r.Undo_EndBlock("LautFunk: LUFS-I und True-Peak Renderziele", -1)
r.MarkProjectDirty(proj)

r.MB(string.format(
  "Render-Konfiguration gesetzt:\n  Integrated LUFS: %.1f\n  True Peak Max: %.1f dBTP\n\nWICHTIG: Datei > Render oeffnen und Einstellungen kontrollieren.\nDas Skript startet keinen Render.\nBei stark dynamischem Material bitte die Analyse nach dem Rendern pruefen.",
  loudness, tp),
  "LautFunk - Renderziele bereit", 0)
