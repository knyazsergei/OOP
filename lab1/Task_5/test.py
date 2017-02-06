import subprocess
cmd = 'ping 8.8.8.8'#E:/education/ООП/lab1.5/Debug/lab1.5.exe E:/education/ООП/lab1.5/lab1.5/test.txt'
p = subprocess.Popen(cmd, shell = True)
stdoutdata, stderrdata = p.communicate()
errorCode=p.returncode
print(errorCode)