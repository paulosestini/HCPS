import os

os.system("g++ -c *.cpp")
os.system("g++ *.o -o program.out -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system")
os.system("rm *.o")
os.system("./program.out")