import os

file1 = open('C:/CP/Main.cpp', 'r')
Lines = file1.readlines()
file1.close()
file1 = open('C:/Users/_swet/Myexe/temp_noob.cpp', 'w')

Includes = []
for line in Lines:
    if line.find("#include") != -1 and line.find("DEBUG.h") == -1:
        Includes.append(line)
    elif line.find("typedef multiset<int> msi;") != -1:
        file1.write("#define msi multiset<int>\n")
    elif line.find("typedef map<int, int> mii;") != -1:
        file1.write("#define mii map<int, int>\n")
    elif line.find("typedef pair<int, int> pii;") != -1:
        file1.write("#define pii pair<int, int>\n")
    elif line.find("const double pi = 3.141592653589793;") != -1:
        file1.write("#define pi 3.141592653589793\n")
    else:
        file1.write(line)
file1.close()
os.system('cmd /c "g++ -E "C:/Users/_swet/Myexe/temp_noob.cpp" -o "C:/CP/Noob.cpp"')
os.remove('C:/Users/_swet/Myexe/temp_noob.cpp')

file1 = open('C:/CP/Noob.cpp', 'r')
Lines = file1.readlines()
file1.close()
file1 = open('C:/CP/Noob.cpp', 'w')

Includes.reverse()
for line in Includes:
    file1.write(line)
file1.write("typedef long long lli;\n")
for line in Lines:
    if line == '\n':
        continue
    line = line.replace("long long", "lli")
    line = line.replace("signed main()", "int main()")
    line = line.replace("code()", "solve()")
    line = line.replace("print(", "out(")
    line = line.replace("printl(", "output(")
    if line.find("#") != 0:
        if line.find("google") == -1 and line.find("__gtest__") == -1:
            file1.write(line)

file1.close()

os.system('cmd /c "g++ -D _SWET -D _BELUGA -D _________________________________________________ '
          '-std=c++17 "C:/CP/Main.cpp" -o "C:/CP/Main.exe"')
os.system('cmd /c "Main.exe<Input.txt>Output.txt"')

