//animal data wrapper class
class Animal{
  //public variables assigned to each animal at instantiation
  public:
    String loc;
    String hex;
    String type;
    bool isFound = false;
  
    //object constructor
    Animal(void) {}
    Animal(String key, String pair, String str){
      setHex(key);
      setLoc(pair);
      setName(str);
    }
    
    //accessor and mutator methods
    void setHex(String s){hex = s;}
    String getHex(void){return hex;}
    
    void setLoc(String s){loc = s;}
    String getLoc(void){return loc;}
    
    void setName(String s){type = s;}
    String getName(void){return type;}
    
    void setFound(bool isVal){isFound = isVal;}
    bool getFound(void){return isFound;}
};//end of class

//global variabler for animal array size
const int animalCount = 16;
Animal animals[animalCount];

void SetupAnimals(void){
  //Instantiating each specific animal object and adding them all to an iteratable animal array
  animals[0] = Animal("5a8eccdd", "57cffb64", "Woodpecker");
  animals[1] = Animal("613abb9d", "438f1ed4", "Rattlesnake");
  animals[2] = Animal("208f7473", "27ecfe64", "Bush");
  animals[3] = Animal("63a61999", "c772b65", "Mushroom");
  animals[4] = Animal("12dfc956", "9769765", "Bacteria");
  animals[5] = Animal("283c856", "7a0465", "Hawk");
  animals[6] = Animal("a92abdd", "27d8f064", "Squirrel");
  animals[7] = Animal("c61a6513", "66aca230", "Mouse");
  animals[8] = Animal("e0d76673", "461adf7d", "Ant");
  animals[9] = Animal("30b97573", "d6d4a030", "Rat");
  animals[10] = Animal("55e22a2a", "4732f664", "Lizard");
  animals[11] = Animal("5225cd56", "86c8187e", "S.Cactus");
  animals[12] = Animal("d25dc356", "4736f164", "Mantis");
  animals[13] = Animal("d7172b70", "4726f65", "P.Cactus");
  animals[14] = Animal("509f7673", "2765165", "Owl");
  animals[15] = Animal("303d7773", "6691327e", "Grasshopper");


}
