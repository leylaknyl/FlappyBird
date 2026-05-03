#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow ana_pencere(sf::VideoMode(600, 400), "flappy bird game");//pencere oluşturduk
    ana_pencere.setFramerateLimit(60);//saniyede en fazla 60 kez çalıştırır

    sf::CircleShape bird_shape(50.f);//karakter tanımlaması yaptık burda 50 piksel yarıçaplı bir daire

    bird_shape.setFillColor(sf::Color::Yellow);//kuşun iç rengi 

    bird_shape.setPosition(250, 150);//kuşun başlangıç konumu belirleniyor(x,y)koordinatları

    float bird_speed=0.0f;// kuşun dikey hızı
    float gravity=0.50f;// her döngüde hıza eklenecek olan yerçekimi
    float engel_x=600.0f;// engelin yataydaki baslangıc konumu
    float engel_speed=3.0f;// engellerin her karede sola doğru kaç piksel hareket edeceğini belirler

    sf::RectangleShape ust_engel(sf::Vector2f(70.0f,150.0f));// üst engel nesnesi oluşturuldu ve genişlik ile yükseklik değerleri atandı

    sf::RectangleShape alt_engel(sf::Vector2f(70.0f,150.0f));// alt engel nesnesi

    //engelleri renklendirme işlemi
    ust_engel.setFillColor(sf::Color::Magenta);
    alt_engel.setFillColor(sf::Color::Magenta);
    //kullanıcıdan gelen olaylar kontrol edilir
    
    while(ana_pencere.isOpen()) {//açık olduğu sürece
        sf::Event etkilesim;//işletim sisteminden gelen etkileşimleri algılar
        while (ana_pencere.pollEvent(etkilesim)) {//sırada bekleyen bir etkilesim var mı
            
            if (etkilesim.type == sf::Event::Closed){
                ana_pencere.close();//pencereyi kapatıp döngüden çıkıyoruz
            }
           
            if(etkilesim.type == sf::Event::KeyPressed){//kullanıcı klavyeden tuşa bastı mı?
                if(etkilesim.key.code == sf::Keyboard::Space){//basılan tuş Space mi degil mi?
                    bird_speed=-8.0f;//yukarı yönlü bir zıplama için negatif bir hız verilir
                }
            }
        }
        
        bird_speed+=gravity;// yerçekimi kuşun hızına eklenir ve kuş her karede daha hızlı düşer
        
        bird_shape.move(0,bird_speed);//yatayda hareket yok ama dikeyde hareket eder (bird_speed kadar).y+:aşağı,y-:yukarı hareket

        engel_x-=engel_speed;// engellerin x konumu azalır ve sola doğru kaymasını sağlar

        ust_engel.setPosition(engel_x,0);//üst engel ekranın üst kısmına yerleştirildi

        alt_engel.setPosition(engel_x,250);//alt engel ekranın altına yerleştirildi

        if(engel_x<-70.0f){ // engel ekrandan çıkarsa tekrar en sağa kaydırma
        engel_x=600.0f;
        }
        
        ana_pencere.clear();//her karede ekran temizlenir
        
        ana_pencere.draw(ust_engel); // engellerin ekrana çizilmesi 
        ana_pencere.draw(alt_engel);
        ana_pencere.draw(bird_shape);//hazırlanan nesne ekrana çiziliyor,kuş engellerden sonra çiziliyor
        
        ana_pencere.display();//ekrana yansıtma 
    }
    return 0;
}