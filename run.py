import os

os.system("rm *.o");
os.system("g++ -c *.cpp")
os.system("g++ *.o -o program.out -lsfml-graphics -lsfml-window -lsfml-system")
os.system("./program.out")