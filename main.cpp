#include <iostream>
#include <cstring>
using namespace std;

//1-day sokoban game by Viie, dont read the source code if (you like being sane || you love yourself) :>

int main() {
  
  system("clear");
  
  bool turnEnd = false, canMoveN, canMoveS, canMoveE, canMoveW, canMoveNB, canMoveSB, canMoveEB, canMoveWB, gamePlaying = true, debugMode = false;
  char input;

  int tiles[110] = {1, 1, 1, 1, 1, 1, 1, 6, 
                    1, 3, 5, 3, 5, 5, 1, 6,
                    1, 5, 5, 2, 5, 5, 1, 6,
                    1, 5, 5, 4, 5, 2, 1, 6,
                    1, 2, 5, 5, 5, 3, 1, 6,
                    1, 5, 5, 5, 2, 3, 1, 6,
                    1, 1, 1, 1, 1, 1, 1, 6};
  int rowCount;
  int hardTiles[] = {1, 7}, hardTileTypes = 2;

  //Levels==================================================
    int lvlcount = 3;
  
    int lv1[] = {1, 1, 1, 1, 1, 1, 1, 6, 
                 1, 3, 5, 3, 5, 5, 1, 6,
                 1, 5, 5, 2, 5, 5, 1, 6,
                 1, 5, 5, 2, 3, 5, 1, 6,
                 1, 5, 5, 2, 3, 5, 1, 6,
                 1, 5, 5, 2, 3, 5, 1, 6,
                 1, 5, 5, 2, 3, 5, 1, 6,
                 1, 5, 5, 4, 5, 2, 1, 6,
                 1, 2, 5, 5, 5, 3, 1, 6,
                 1, 5, 5, 5, 2, 3, 1, 6,
                 1, 1, 1, 1, 1, 1, 1, 6};
  
    int lv2[] = {1, 1, 1, 1, 1, 1, 1, 1, 6, 
                 1, 3, 5, 3, 5, 5, 5, 1, 6,
                 1, 5, 5, 2, 5, 5, 5, 1, 6,
                 1, 5, 5, 4, 5, 2, 5, 1, 6,
                 1, 2, 5, 5, 5, 3, 5, 1, 6,
                 1, 5, 5, 5, 2, 3, 5, 1, 6,
                 1, 1, 1, 1, 1, 1, 1, 1, 6};
  
    int lv3[] = {5, 5, 5, 1, 1, 1, 1, 6, 
                 5, 5, 5, 1, 5, 5, 1, 6,
                 5, 5, 5, 1, 5, 5, 1, 6,
                 5, 5, 1, 5, 5, 2, 1, 6,
                 1, 1, 1, 5, 5, 3, 1, 6,
                 1, 4, 5, 5, 2, 3, 1, 6,
                 1, 1, 1, 1, 1, 1, 1, 6};
  int r1 = 8, r2 = 9, r3 = 8;
  //Levels==================================================

  srand(time(0));
  int lvl = (rand() % lvlcount) + 1;

  if(lvl == 1) {memcpy(tiles, lv1, sizeof(lv1)); rowCount = r1;}
  if(lvl == 2) {memcpy(tiles, lv2, sizeof(lv2)); rowCount = r2;}
  if(lvl == 3) {memcpy(tiles, lv3, sizeof(lv3)); rowCount = r3;}

  int tileNo = *(&tiles+1) - tiles, playerPos = 0;
  
  bool checkBox(int tiles[], int tileN);
  // void boxPush(int tiles[], int t, int boxpos, int r, char in);
  void updateField(int tiles[], int tileN);

  cout << "Welcome to Sokoban! \nControls are wasd\nInput q to quit\n\n";

  updateField(tiles, tileNo);
  
  while(gamePlaying){
      //Reinitialize variables
      playerPos = 0;
      canMoveN = false;
      canMoveS = false;
      canMoveE = false;
      canMoveW = false;
      canMoveNB = false;
      canMoveSB = false;
      canMoveEB = false;
      canMoveWB = false;
        
      cout << "\nInput Movement (wasd): ";
      cin >> input;
    
      //Count player's spot in the array
      for(int i = 0; i < tileNo + 1; i++) { 
          if(tiles[i] != 4) {
            playerPos++;
          }
            
          else
            break;
      }
      
      //Check if player can move in certain direction
      for(int i = 0; i < hardTileTypes; i++) { 
        if(tiles[playerPos - rowCount] != hardTiles[i]) canMoveN = true;
        else{canMoveN = false; break;}
        }
        
      for(int i = 0; i < hardTileTypes; i++) { 
        if(tiles[playerPos + rowCount] != hardTiles[i]) canMoveS = true;
        else{canMoveS = false; break;}
        }
        
      for(int i = 0; i < hardTileTypes; i++) { 
        if(tiles[playerPos + 1] != hardTiles[i]) canMoveE = true;
        else{canMoveE = false; break;}
        }
        
      for(int i = 0; i < hardTileTypes; i++) { 
        if(tiles[playerPos - 1] != hardTiles[i]) canMoveW = true;
        else{canMoveW = false; break;}
        }

      //Special Checking
      for(int i = 0; i < hardTileTypes; i++) { 
        if(tiles[playerPos - rowCount] != hardTiles[i] && tiles[playerPos - rowCount - rowCount] != hardTiles[i]) canMoveNB = true;
        else{canMoveNB = false; break;}
        }
        
      for(int i = 0; i < hardTileTypes; i++) { 
        if(tiles[playerPos + rowCount] != hardTiles[i] && tiles[playerPos + rowCount + rowCount] != hardTiles[i]) canMoveSB = true;
        else{canMoveSB = false; break;}
        }
        
      for(int i = 0; i < hardTileTypes; i++) { 
        if(tiles[playerPos + 1] != hardTiles[i] && tiles[playerPos + 2] != hardTiles[i]) canMoveEB = true;
        else{canMoveEB = false; break;}
        }
        
      for(int i = 0; i < hardTileTypes; i++) { 
        if(tiles[playerPos - 1] != hardTiles[i] && tiles[playerPos - 2] != hardTiles[i]) canMoveWB = true;
        else{canMoveWB = false; break;}
        }
        

      //move player: start

      if(input == 'e') debugMode = true;
        
      else if(input == 'q') gamePlaying = false;
    
      else if(input == 'w' && canMoveN && tiles[playerPos - rowCount] != 2 && tiles[playerPos - rowCount] != 3) {
        tiles[playerPos] = 5;
        tiles[playerPos - rowCount] = 4;
      }
    
      else if(input == 'a' && canMoveW && tiles[playerPos - 1] != 2 && tiles[playerPos - 1] != 3) {
        tiles[playerPos] = 5;
        tiles[playerPos - 1] = 4;
      }
    
      else if(input == 's' && canMoveS && tiles[playerPos + rowCount] != 2 && tiles[playerPos + rowCount] != 3) {
        tiles[playerPos] = 5;
        tiles[playerPos + rowCount] = 4;
      }
    
      else if(input == 'd' && canMoveE && tiles[playerPos + 1] != 2 && tiles[playerPos + 1] != 3) {
        tiles[playerPos] = 5;
        tiles[playerPos + 1] = 4;
      }


    
      else if(input == 'w' && canMoveNB && tiles[playerPos - rowCount] == 2 && tiles[playerPos - rowCount - rowCount] != 2) {
        tiles[playerPos] = 5;
        tiles[playerPos - rowCount] = 4;

        // boxPush(tiles, tileNo, playerPos - rowCount, rowCount, input);
        
        
        if(tiles[playerPos - rowCount - rowCount] == 3){
          tiles[playerPos - rowCount - rowCount] = 7;
          }
        else tiles[playerPos - rowCount - rowCount] = 2;
        
      }
    
      else if(input == 'a' && canMoveWB && tiles[playerPos - 1] == 2 && tiles[playerPos - 2] != 2) {
        tiles[playerPos] = 5;
        tiles[playerPos - 1] = 4;

        // boxPush(tiles, tileNo, playerPos - rowCount, rowCount, input);
        
        
        if(tiles[playerPos - 2] == 3){
          tiles[playerPos - 2] = 7;
          }
        else tiles[playerPos - 2] = 2;
        
      }
    
      else if(input == 's' && canMoveSB && tiles[playerPos + rowCount] == 2 && tiles[playerPos + rowCount + rowCount] != 2) {
        tiles[playerPos] = 5;
        tiles[playerPos + rowCount] = 4;

        // boxPush(tiles, tileNo, playerPos - rowCount, rowCount, input);
        
        
        if(tiles[playerPos + rowCount + rowCount] == 3){
          tiles[playerPos + rowCount + rowCount] = 7;
          }
        else tiles[playerPos + rowCount + rowCount] = 2;
        
      }
    
      else if(input == 'd' && canMoveEB && tiles[playerPos + 1] == 2 && tiles[playerPos + 2] != 2) {
        tiles[playerPos] = 5;
        tiles[playerPos + 1] = 4;

        // boxPush(tiles, tileNo, playerPos - rowCount, rowCount, input);
        
        
        if(tiles[playerPos + 2] == 3){
          tiles[playerPos + 2] = 7;
          }
        else tiles[playerPos + 2] = 2;
        
      }

      //move player: end

      system("clear");

      if(debugMode) {
      cout << "Valid movement:";
      cout << canMoveS;
      cout << canMoveN;
      cout << canMoveE;
      cout << canMoveW;
      cout << canMoveNB;
      cout << canMoveEB;
      cout << canMoveSB;
      cout << canMoveWB;
      cout << "\n";}

      gamePlaying = checkBox(tiles, tileNo);

      //redraw field
      updateField(tiles, tileNo);
      
  }
  
}
  
  void updateField(int field[], int tileN) {
      for(int i = 0; i < tileN; i++) {
      if(field[i] == 1) { //Wall
        cout << "% ";
      }
  
      else if(field[i] == 2) { //Box
        cout << "# ";
      }
  
      else if(field[i] == 3) { //Point
        cout << "+ ";
      }
  
      else if(field[i] == 4) { //Player
        cout << "@ ";
      }
  
      else if(field[i] == 5) { //Empty
        cout << "  ";
      }
  
      else if(field[i] == 6) { //End Line
        cout << endl;
      }
        
      else if(field[i] == 7) { //End Line
        cout << "= ";
      }
        
    }
  }

  // void boxPush(int tiles[], int t, int boxpos, int r, char in) {
    // 
  // }

  bool checkBox(int field[], int tileN) {
    bool a = false;
    for(int i = 0; i < tileN; i++) {
      if(field[i] == 2){a = true; break;}
    }
    if(a) return true;
    else return false;
  }
