rem @echo off
SET program="%1"
if %program% == "" goto err

mkdir OUT
echo "1"
%program% "test\input.txt" "OUT\out1.txt" "ma" "mama"
if ERRORLEVEL 1 goto testFailed
fc.exe "OUT\out1.txt" "standart\ma.txt"
if ERRORLEVEL 1 goto testFailed

echo "2"
%program% "test\input.txt" "OUT\out2.txt" "1231234" "TABULATION"
if ERRORLEVEL 1 goto testFailed
fc.exe "OUT\out2.txt" "standart\tab.txt"
if ERRORLEVEL 1 goto testFailed

echo "3"
%program% "test\input.txt" "OUT\out3.txt" "123" "ASDASASDABSJDGABSJDGBASBDJBASDHBKAHSBDHBASDBAKHSDBHASBHDKASBHDBHJASBHDASBHDABJHSDBHAASDABSJDGABSJDGBASBDJBASDHBKAHSBDHBASDBAKHSDBHASBHDKASBHDBHJASBHDASBHDABJHSDBHAASDABSJDGABSJDGBASBDJBASDHBKAHSBDHBASDBAKHSDBHASBHDKASBHDBHJASBHDASBHDABJHSDBHAASDABSJDGABSJDGBASBDJBASDHBKAHSBDHBASDBAKHSDBHASBHDKASBHDBHJASBHDASBHDABJHSDBHADASDAHGDAGVSDGHSADASGHDGHASDGHASSDASASGHDGHASDGHASSDASDASDASDASDHASHGDAGVS"
if ERRORLEVEL 1 goto testFailed
fc.exe "OUT\out3.txt" "standart\longStr.txt"
if ERRORLEVEL 1 goto testFailed

echo "4"
%program% "test\input.txt" "OUT\out4.txt" "peace" ""
if ERRORLEVEL 1 goto testFailed
fc.exe "OUT\out4.txt" "standart\str_to_space.txt"
if ERRORLEVEL 1 goto testFailed

echo "5"
%program% "test\input.txt" "OUT\out5.txt" "" "CAPS LOCK"
if ERRORLEVEL 1 goto testFailed
fc.exe "OUT\out5.txt" "standart\space_to_str.txt"
if ERRORLEVEL 1 goto testFailed

echo OK
exit /B

:testFailed
echo Testing failed
exit /B

:err
echo Usage: test.bat <Path to program>