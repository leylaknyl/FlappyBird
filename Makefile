# Derleyici
CXX = g++

# Header dosyalarının bulunduğu klasör
CXXFLAGS = -Iinclude

# Kullanılan SFML kütüphaneleri
LDFLAGS = -Llib -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system

# Kaynak dosyalar
SRC = src/main.cpp src/Pipe.cpp

# Çıktı dosyası
OUT = bin/main.exe

all:
	$(CXX) $(SRC) $(CXXFLAGS) $(LDFLAGS) -o $(OUT)

run: all
	./$(OUT)

clean:
	if exist $(OUT) del $(OUT)