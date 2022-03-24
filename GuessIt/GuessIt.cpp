#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <string.h>
#include <time.h>
#include <cstdlib>
#include <windows.h>

using namespace std;

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 600;
const string WINDOW_TITLE = "Guess It";
int firstDigitPos[2] = {44, 460};
int secondDigitPos[2] = {69, 500};
int startPoint = 1, endPoint = 100;

string response = "";

string guess = "";
string nums[10] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
int positions[2] = {400, 440};
void logSDLError(std::ostream& os,
                 const std::string &msg, bool fatal = false);
void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);
void quitSDL(SDL_Window* window, SDL_Renderer* renderer);
void waitUntilKeyPressed();
void renderTexture(SDL_Texture* texture, SDL_Renderer* renderer, int x, int y);
void renderTexture(SDL_Texture* texture, SDL_Renderer* renderer, int x, int y, int w, int h);


int generateRandomNumber();
int PlayerGuess() ;
int fontHeight = 36;
SDL_Texture* loadTexture( string path, SDL_Renderer* renderer );
string interpretKey(SDL_KeyboardEvent* key);

int generateRandomNumber();
int playerGuess(SDL_Window* &window, SDL_Renderer* &renderer, SDL_Texture* num[]);
void renderGuess(SDL_Texture* texture, SDL_Renderer* &renderer, int posX, int posY);
void renderResponse(SDL_Texture* texture, SDL_Renderer* &renderer,int y, int textureWidth);
void refreshScreen(SDL_Window* window, SDL_Renderer* renderer, SDL_Texture* background, SDL_Texture* Henderson, SDL_Rect& HendersonRect, SDL_Texture* Screen, SDL_Rect& ScreenRect, SDL_Texture* Left, SDL_Rect& LeftRect);
void printAnswer(int guess, int answer, SDL_Window* window, SDL_Renderer* &renderer, SDL_Texture* background, SDL_Texture* &Small, SDL_Texture* &Big, SDL_Rect& SmallRect, SDL_Rect& BigRect,SDL_Texture* &Congrat, SDL_Rect& CongratRect, SDL_Texture* Henderson, SDL_Rect& HendersonRect, SDL_Texture* Screen, SDL_Rect& ScreenRect, SDL_Texture* Left, SDL_Rect& LeftRect);
void renderResponse(SDL_Texture* texture, int y, int textureWidth);
void playGame(bool &isRunning, int &secretNumber, SDL_Window* &window, SDL_Renderer* &renderer, SDL_Texture* background, SDL_Texture* num[], SDL_Texture* &Small, SDL_Texture* &Big, SDL_Rect& SmallRect, SDL_Rect& BigRect,SDL_Texture* &Congrat, SDL_Rect& CongratRect, SDL_Texture* Henderson, SDL_Rect& HendersonRect, SDL_Texture* Screen, SDL_Rect& ScreenRect, SDL_Texture* Left, SDL_Rect& LeftRect);
int main(int argc, char *argv[])
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer);

    SDL_Texture* background = loadTexture("Anfield.png", renderer);
    SDL_RenderCopy( renderer, background, NULL, NULL);

    SDL_RenderPresent( renderer );
    waitUntilKeyPressed();

    SDL_Texture* Left = loadTexture("left.png", renderer);
    SDL_Rect LeftRect;
    SDL_QueryTexture(Left, NULL, NULL, &LeftRect.w, &LeftRect.h);
    LeftRect.x = 300;
    LeftRect.y = 100;
    LeftRect.w = LeftRect.w/1.2;
    LeftRect.h = LeftRect.h/1.8;
    SDL_RenderCopy( renderer, Left, NULL, &LeftRect );

    SDL_Texture* Henderson = loadTexture("Henderson.png", renderer);
    SDL_Rect HendersonRect;
    SDL_QueryTexture(Henderson, NULL, NULL, &HendersonRect.w, &HendersonRect.h);
    HendersonRect.x = 20;
    HendersonRect.y = 50;
    HendersonRect.w = HendersonRect.w/0.7;
    HendersonRect.h = HendersonRect.h/0.7;
    SDL_RenderCopy( renderer, Henderson, NULL, &HendersonRect );

    SDL_Texture* Screen = loadTexture("screen.png", renderer);
    SDL_Rect ScreenRect;
    SDL_QueryTexture(Screen, NULL, NULL, &ScreenRect.w, &ScreenRect.h);
    ScreenRect.x = 450;
    ScreenRect.y = 350;
    ScreenRect.w = ScreenRect.w/1.5;
    ScreenRect.h = ScreenRect.h/1.7;
    SDL_RenderCopy( renderer, Screen, NULL, &ScreenRect );

    SDL_Texture* Small = loadTexture("small.png", renderer);
    SDL_Rect SmallRect;
    SDL_QueryTexture(Small, NULL, NULL, &SmallRect.w, &SmallRect.h);
    SmallRect.x = 550;
    SmallRect.y = 450;
    SmallRect.w = SmallRect.w/1.0;
    SmallRect.h = SmallRect.h/1.0;

    SDL_Texture* Big = loadTexture("big.png", renderer);
    SDL_Rect BigRect;
    SDL_QueryTexture(Big, NULL, NULL, &BigRect.w, &BigRect.h);
    BigRect.x = 550;
    BigRect.y = 450;
    BigRect.w = BigRect.w/1.0;
    BigRect.h = BigRect.h/1.0;

    SDL_Texture* Congrat = loadTexture("congrat.png", renderer);
    SDL_Rect CongratRect;
    SDL_QueryTexture(Congrat, NULL, NULL, &CongratRect.w, &CongratRect.h);
    CongratRect.x = 550;
    CongratRect.y = 450;
    CongratRect.w = CongratRect.w/1.0;
    CongratRect.h = CongratRect.h/1.0;

    SDL_Texture* num[10];
    for(int i=0;i<10;i++)
    {
        num[i]=loadTexture(to_string(i) + ".png" ,renderer);
    }



    SDL_RenderPresent( renderer );
    waitUntilKeyPressed();

    bool isRunning = true;
    int secretNumber = generateRandomNumber();
    while (isRunning) {
        playGame(isRunning, secretNumber, window, renderer,background, num, Small, Big, SmallRect, BigRect, Congrat, CongratRect, Henderson, HendersonRect, Left, LeftRect, Screen, ScreenRect);
    }

    return 0;

    //Free loaded image
    SDL_DestroyTexture( Left );
    Left = NULL;
    SDL_DestroyTexture( Screen );
    Screen = NULL;
    SDL_DestroyTexture( Henderson );
    Henderson = NULL;
    SDL_DestroyTexture( background );
    background = NULL;
    SDL_DestroyTexture( Big );
    Big = NULL;
    SDL_DestroyTexture( Small );
    Small = NULL;
    SDL_DestroyTexture( Congrat );
    Congrat = NULL;

    for (int i = 0; i < 10; i++) {
        SDL_DestroyTexture(num[i]);
    }

    quitSDL(window, renderer);
    return 0;
}




int generateRandomNumber()
{
    return rand() % 100;
}

int playerGuess(SDL_Window* &window, SDL_Renderer* &renderer, SDL_Texture* num[] ) {
    string currentGuess = "";
    bool isListening = true;
    SDL_Event event;
    while(SDL_PollEvent(&event) || isListening) {
        if (event.type == SDL_QUIT) {
            isListening = false;

            quitSDL(window, renderer);
        }
        if (event.type == SDL_KEYDOWN) {
            if (interpretKey(&event.key) == "Return") {
                isListening = false;
            }
            const string pressedKey = interpretKey(&event.key);
                if (currentGuess.length() < 2)
                {

                currentGuess += pressedKey;
                for (int i = 0; i < currentGuess.length(); i++) {
                    int currentNum = currentGuess[i] - 48;
                    renderGuess(num[currentNum], renderer, positions[i], 200);
                }
                SDL_RenderPresent(renderer);
                }
        }
    }
    int answer = currentGuess.length() > 0 ? stoi(currentGuess) : 1;
    guess = currentGuess;
    return answer;
}

void renderGuess(SDL_Texture* texture, SDL_Renderer* &renderer, int posX, int posY) {
    renderTexture(texture, renderer, posX, posY, 36, fontHeight);
}

void renderResponse(SDL_Texture* texture, SDL_Renderer* &renderer,int y, int textureWidth) {
    renderTexture(texture, renderer, 450, y, textureWidth, fontHeight);
}



void printAnswer(int guess, int answer, SDL_Window* window, SDL_Renderer* &renderer,SDL_Texture* background, SDL_Texture* &Small, SDL_Texture* &Big, SDL_Rect& SmallRect, SDL_Rect& BigRect,SDL_Texture* &Congrat, SDL_Rect& CongratRect,SDL_Texture* Henderson, SDL_Rect& HendersonRect, SDL_Texture* Screen, SDL_Rect& ScreenRect, SDL_Texture* Left, SDL_Rect& LeftRect  ) {
    refreshScreen(window, renderer, background, Henderson, HendersonRect, Screen, ScreenRect, Left, LeftRect);
    if (guess == answer) {
        SDL_RenderCopy( renderer, Congrat, NULL, &CongratRect );
        cout << "Exactly. Congratulation!";
        SDL_RenderPresent (renderer);
    } else if (guess < answer) {
        SDL_RenderCopy( renderer, Small, NULL, &SmallRect );
        cout << "Your number is small!";
        SDL_RenderPresent (renderer);
                SDL_Delay(2000);
                refreshScreen(window, renderer, background, Henderson, HendersonRect, Screen, ScreenRect, Left, LeftRect);

    } else {
        SDL_RenderCopy( renderer, Big, NULL, &BigRect );
        cout << "Your number is big!";
        SDL_RenderPresent (renderer);
        SDL_Delay(2000);
        refreshScreen(window, renderer, background, Henderson, HendersonRect, Screen, ScreenRect, Left, LeftRect);

    }
    cout << endl;
}

int getSolution(int guess) {
    string answer;
    cout << "Is " << guess << " your number? (yes: y; bigger: b; smaller: s): ";
    cin >> answer;
    return answer == "y" ? 0 : (answer == "b" ? 1 : 2);
}

SDL_Texture* loadTexture( string path, SDL_Renderer* renderer )
{
    SDL_Texture* newTexture = nullptr;
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if ( loadedSurface == nullptr )
        cout << "Unable to load image " << path << " SDL_image Error: "
             << IMG_GetError() << endl;
    else {
        newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
        if( newTexture == nullptr )
            cout << "Unable to create texture from " << path << " SDL Error: "
                 << SDL_GetError() << endl;
        SDL_FreeSurface( loadedSurface );
    }
    return newTexture;
}

void logSDLError(std::ostream& os,
                 const std::string &msg, bool fatal)
{
    os << msg << " Error: " << SDL_GetError() << std::endl;
    if (fatal) {
        SDL_Quit();
        exit(1);
    }
}

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logSDLError(std::cout, "SDL_Init", true);

    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
       SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    //window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
      // SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP);
    if (window == nullptr) logSDLError(std::cout, "CreateWindow", true);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
                                              SDL_RENDERER_PRESENTVSYNC);
    //renderer = SDL_CreateSoftwareRenderer(SDL_GetWindowSurface(window));

    if (renderer == nullptr) logSDLError(std::cout, "CreateRenderer", true);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void renderTexture(SDL_Texture* texture, SDL_Renderer* renderer, int x, int y) {
    SDL_Rect destinationRec;
    destinationRec.x = x;
    destinationRec.y = y;

    SDL_QueryTexture(texture, NULL, NULL, &destinationRec.w, &destinationRec.h);

    SDL_RenderCopy(renderer, texture, NULL, &destinationRec);
}

void renderTexture(SDL_Texture* texture, SDL_Renderer* renderer, int x, int y, int w, int h) {

    SDL_Rect destinationRec;
    destinationRec.x = x;
    destinationRec.y = y;
    destinationRec.w = w;
    destinationRec.h = h;

    SDL_RenderCopy(renderer, texture, NULL, &destinationRec);
}

void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if ( SDL_WaitEvent(&e) != 0 &&
             (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay(150);
    }
}

string interpretKey(SDL_KeyboardEvent* key) {
    return SDL_GetKeyName(key -> keysym.sym);
}
void refreshScreen(SDL_Window* window, SDL_Renderer* renderer, SDL_Texture* background, SDL_Texture* Henderson, SDL_Rect& HendersonRect, SDL_Texture* Screen, SDL_Rect& ScreenRect, SDL_Texture* Left, SDL_Rect& LeftRect){
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, background, nullptr, nullptr);
    SDL_RenderCopy( renderer, Screen, NULL, &ScreenRect );
    SDL_RenderCopy( renderer, Henderson, NULL, &HendersonRect );
    SDL_RenderCopy( renderer, Left, NULL, &LeftRect );
    SDL_RenderPresent(renderer);
}
void playGame(bool &isRunning, int &secretNumber, SDL_Window* &window, SDL_Renderer* &renderer,SDL_Texture* background, SDL_Texture* num[], SDL_Texture* &Small, SDL_Texture* &Big, SDL_Rect& SmallRect, SDL_Rect& BigRect,SDL_Texture* &Congrat, SDL_Rect& CongratRect, SDL_Texture* Henderson, SDL_Rect& HendersonRect, SDL_Texture* Screen, SDL_Rect& ScreenRect, SDL_Texture* Left, SDL_Rect& LeftRect ) {

        // get player's guess
        int playerNumber = playerGuess(window, renderer, num);

        // print result
        printAnswer(playerNumber, secretNumber,window, renderer, background, Small, Big, SmallRect, BigRect, Congrat, CongratRect, Henderson, HendersonRect, Left, LeftRect, Screen, ScreenRect);



        // if play won, then ask player to play again
        if (playerNumber == secretNumber) {

            }
}

