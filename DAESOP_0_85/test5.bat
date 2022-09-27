daesop /xh sample.res 3 3h.bin
rem convert EOB 3
daesop /cob eye.res eye_cn1.res
daesop /rh eye_cn1.res 3 3h.bin eye_cn2.res
daesop /e eye_cn2.res Backdrop bkgnd.bmp
rem convert HACK.RES from Dungeon Hack (not very useful)
daesop /convert_old_bitmaps hack.res hack_cn1.res
daesop /rh hack_cn1.res 3 3h.bin hack_cn2.res








