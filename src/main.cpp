#include <SFML/Graphics.hpp>
#include "../include/Pipe.h"
#include <string>//skoru metne çevirmek için



int main() {
    sf::RenderWindow ana_pencere(sf::VideoMode(600, 400), "flappy bird game");//pencere oluşturduk

    ana_pencere.setFramerateLimit(60);//saniyede en fazla 60 kez çalıştırır

    sf::CircleShape bird_shape(20.f);//karakter tanımlaması yaptık burda 25 piksel yarıçaplı bir daire

    sf::Texture bird_texture; // kuş görselini belleğe yüklemek için texture nesnesi

    bird_texture.loadFromFile("assets/images/bird.png"); // bird.png dosyası projeden yüklenir

    sf::Sprite bird_sprite; // kuş görselini ekranda gösterecek sprite nesnesi

    bird_sprite.setTexture(bird_texture); // yüklenen texture sprite'a bağlanır

    bird_sprite.setScale(0.08f, 0.08f); // kuş görselinin boyutu küçültülür

    bird_sprite.setPosition(250,150); // kuşun başlangıç konumu ayarlanır

    bird_shape.setFillColor(sf::Color::Yellow);//kuşun iç rengi 

    bird_shape.setPosition(250, 150);//kuşun başlangıç konumu belirleniyor(x,y)koordinatları

    // arka plan görselini belleğe yüklemek için texture nesnesi oluşturuldu
    sf::Texture background_texture;

    // background.png dosyası assets klasöründen yüklenir
    background_texture.loadFromFile("assets/images/background.png");

    // arka plan görselini ekranda gösterecek sprite nesnesi oluşturuldu
    sf::Sprite background_sprite;

    // yüklenen texture sprite nesnesine bağlanır
    background_sprite.setTexture(background_texture);

    //arka plan görseli pencere boyutuna göre ayarlanır
    background_sprite.setScale(
    600.0f / background_texture.getSize().x,
    400.0f / background_texture.getSize().y
);

    //arka plan başlangıç konumu ayarlanır
    background_sprite.setPosition(0,0);

    float bird_speed=0.0f;// kuşun dikey hızı

    float gravity=0.50f;// her döngüde hıza eklenecek olan yerçekimi
 
    int skor=0;//oyuncunun mevcut puanını tutar
    int en_yuksek_skor = 0; // oyun boyunca ulaşılan en yüksek skor tutulur
    bool skor_alindi=false;//aynı engelden sadece bir kez puan alınmasını kontrol eder

    bool oyun_basladi=false;//oyun başlamadan önce başlangıç ekranını göstermek için

    bool oyun_bitti=false;// oyun bitince game  over ekranını göstermek için

    Pipe pipe;// Pipe sınıfından engel sistemi oluşturuldu
    
    sf::Font font;//yazı tipi için font nesnesi

    //font dosyası assets klasöründen yüklendi.
    font.loadFromFile("assets/fonts/ARIALI.TTF");

    sf::Text skor_yazi;// skorun ekranda gösterileceği yazı nesnesi
    sf::Text best_yazi; // en yüksek skorun gösterileceği yazı nesnesi

    skor_yazi.setFont(font);//skor yazısında kullanılacak font ayarlandı
    skor_yazi.setCharacterSize(28);//skor yazısının boyutu
    skor_yazi.setFillColor(sf::Color::Black);//skorun rengi
    skor_yazi.setPosition(20,20);//skor yazısının ekrandaki konumu ayarlandı
    skor_yazi.setStyle(sf::Text::Bold);

    best_yazi.setFont(font); // best score yazısında kullanılacak font ayarlanır

    best_yazi.setCharacterSize(25); // yazı boyutu ayarlanır

    best_yazi.setFillColor(sf::Color::Black); // yazı rengi beyaz yapılır

    best_yazi.setPosition(20,60); // yazının ekrandaki konumu ayarlanır

    best_yazi.setStyle(sf::Text::Bold);
    sf::Text baslangic_yazi; // oyun başlamadan önce ekranda gösterilecek yazı

    baslangic_yazi.setFont(font); // yazının kullanacağı font belirlenir
    baslangic_yazi.setCharacterSize(50); // yazı boyutu ayarlanır
    baslangic_yazi.setStyle(sf::Text::Bold); // yazı kalın yapılır
    baslangic_yazi.setFillColor(sf::Color::White); // yazı rengi beyaz yapılır
    baslangic_yazi.setString("FLAPPY BIRD\nPRESS SPACE"); // başlangıç ekranında yazacak metin
    baslangic_yazi.setPosition(110, 120); // yazının ekrandaki konumu ayarlanır

    sf::Text gameover_yazi; // oyun bitince ekranda gösterilecek yazı

    gameover_yazi.setFont(font); // game over yazısının fontu ayarlanır
    gameover_yazi.setCharacterSize(40); // yazı boyutu ayarlanır
    gameover_yazi.setStyle(sf::Text::Bold); // yazı kalın yapılır
    gameover_yazi.setFillColor(sf::Color::White); // yazı rengi beyaz yapılır
    gameover_yazi.setString("GAME OVER\nPRESS R"); // oyun bitince gösterilecek metin
    
    gameover_yazi.setPosition(150, 140); // yazının ekrandaki konumu ayarlanır


    while(ana_pencere.isOpen()) {//açık olduğu sürece
        sf::Event etkilesim;//işletim sisteminden gelen etkileşimleri algılar
        while (ana_pencere.pollEvent(etkilesim)) {//sırada bekleyen bir etkilesim var mı
            
            if (etkilesim.type == sf::Event::Closed){
                ana_pencere.close();//pencereyi kapatıp döngüden çıkıyoruz
            }
           
            if(etkilesim.type == sf::Event::KeyPressed){//kullanıcı klavyeden tuşa bastı mı?
                if(etkilesim.key.code == sf::Keyboard::Space){//basılan tuş Space mi degil mi?

                    oyun_basladi=true;//space basılınca oyun başlar
                    bird_speed=-6.0f;//yukarı yönlü bir zıplama için negatif bir hız verilir
                }

                // Oyun bittiyse R tuşuna basıldığında kuş başlangıç durumuna döner
                if(etkilesim.key.code == sf::Keyboard::R && oyun_bitti == true){

                bird_sprite.setPosition(250,150); // kuş başlangıç konumuna alınır

                bird_speed = 0.0f; // kuşun dikey hızı sıfırlanır

                skor = 0; // skor sıfırlanır

                skor_alindi = false; // yeni skor alımı için kontrol sıfırlanır

                pipe.reset();//engelleri başlangıç konumuna döndürülür

                oyun_bitti = false; // game over durumu kapatılır

                oyun_basladi = false; // oyun tekrar başlangıç ekranına döner
                }
            }
        }
        
        //skor,çarpışma ve sınır kontrolleri de burada kalacak
        if(oyun_basladi && oyun_bitti==false){

            bird_speed+=gravity;// yerçekimi kuşun hızına eklenir ve kuş her karede daha hızlı düşer
        
            bird_sprite.move(0,bird_speed);//yatayda hareket yok ama dikeyde hareket eder (bird_speed kadar).y+:aşağı,y-:yukarı hareket

            pipe.update();//engeller güncelleniyor,fonksiyonun çağrılması

        

        //engel kuşun arkasında kaldıysa ve bu engelden daha önce puan alınmadıysa skor arttırılır
        if (pipe.get_x() + 70 < bird_sprite.getPosition().x && skor_alindi == false) {
         skor++;
         skor_alindi = true;
        }

        //engel tekrar sağ tarafa geldiğinde yeni skor alınabilmesi için kontrol sıfırlanır
        if (pipe.get_x() > 590) {
        skor_alindi = false;
        }


        // kuş engellere çarptıysa oyun biter
        if (pipe.check_collision(bird_sprite)) {
            oyun_bitti=true;
        }

        //kuş ekranın üstüne çıkarsa veya yere düşerse oyun kapansın
        if(
            bird_sprite.getPosition().y<0 // kuş ekran üstüne çıkmışsa
            || bird_sprite.getPosition().y +
            50 >400
        )
        {
           oyun_bitti=true;
        }
    }

        // mevcut skor en yüksek skordan büyükse yeni en yüksek skor kaydedilir
        if (skor > en_yuksek_skor) {
            en_yuksek_skor = skor;
        }   

        // Skor değeri ekranda gösterilecek yazıya çevrilir
        skor_yazi.setString("Skore: " + std::to_string(skor));

        // en yüksek skor değeri yazıya çevrilerek ekranda gösterilir
        best_yazi.setString("Best Score: " + std::to_string(en_yuksek_skor));

        ana_pencere.clear();//her karede ekran temizlenir

        ana_pencere.draw(background_sprite); // arka plan görseli ekrana çizdirilir

        pipe.draw(ana_pencere); // engellerin ekrana çizilmesi
       
        ana_pencere.draw(bird_sprite); // kuş görseli ekrana çizdirilir

        ana_pencere.draw(skor_yazi);//skor yazısı ekrana çizilir
    
        ana_pencere.draw(best_yazi); // en yüksek skor yazısı ekrana çizilir

        //oyun başlamadıysa başlangıç yazısı çizilir.
        if(!oyun_basladi){
            ana_pencere.draw(baslangic_yazi);
        }

        //oyun bittiyse game over yazısı çizilir.
        if(oyun_bitti){
            ana_pencere.draw(gameover_yazi);
        }

        ana_pencere.display();//ekrana yansıtma 
    }
    return 0;
} 