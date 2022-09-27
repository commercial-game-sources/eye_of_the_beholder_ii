rem converts EYE.RES to EYE2.RES usable in AESOP/32
rem rename the result file to EYE.RES and use in AESOP/32
daesop /eob3conv eye.res eye1.res
daesop /xh sample.res 3 3h.bin
daesop /rh eye1.res 3 3h.bin eye2.res







