import os

os.system("g++ -c *.cpp")
os.system("g++ -c Interface/*.cpp")
os.system("g++ -c Presets/*.cpp")
os.system("g++ -c Simulation/*.cpp")
os.system("g++ -c Utils/*.cpp")

os.system("g++ *.o -o program.out -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system")

os.system("rm *.o")
os.system("./program.out")