#ifndef ASCIIRabbit_h
#define ASCIIRabbit_h

// Rabbit for Trigger port
void showRabbit(WiFiClient& client) {
  client.println();
  client.println("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-");
  client.println("                  _                       _____________________________");
  client.println("                 /_\\                     /    HELLO, MY FRIEND!       /"); 
  client.println("                 \\  \\     ___           /   THANKS FOR THE CARROT!   /");      
  client.println("                  \\  \\   /   \\         /  LET ME SHOW YOU MY HOME:  /");        
  client.println("                   \\  \\_/ \\   \\       /         PORT: " + String(hiddenPort) + "         /");//
  client.println("                    \\     /\\__/      /     USERNAME: " + hiddenUsername + "     /");//
  client.println("                     \\O -/          /     PASSWORD: " + hiddenPassword + "     /");//
  client.println("                  ___/ ^ \\___      / ___________________________/");
  client.println("                     \\___/        /_/");
  client.println("                     _/ \\_");
  client.println("                  __//   \\\\__");
  client.println("                 /___\\/_\\/___\\");
  client.println("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-");
  client.flush();
}

// fake Rabbit
void sendFakeRabbit(WiFiClient& client, bool wrongOnTrigger) {
  client.println();
  client.println("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-");
  if (wrongOnTrigger) {
    client.println("                  ___     __");
    client.println("                 /   \\   /  \\        _______________________");
    client.println("                /   / \\_/ \\  \\      /    WHO ARE YOU?       /");
    client.println("                \\__/\\     /\\_/     / YOU ARE NOT MY FRIEND!/");
    client.println("                     \\O O/        /    GET OUT OF HERE!   /");
    client.println("                  ___/ ^ \\___    / ______________________/");
  } else {
    client.println("                      ____");
    client.println("            z     z  /    \\          ___________________________");
    client.println("                    /     \\\\        /      I AM SLEEPING...     /");
    client.println("                Z   ======= )      /     Z..z..Z..z..Z..z...   /");
    client.println("                     \\- -/ <>     / JUST LEAVE ME A CARROT... /");
    client.println("                z ___/ ^ \\___    / __________________________/");
  }
  client.println("                     \\___/      /_/");
  client.println("                     _/ \\_");
  client.println("                  __//   \\\\__");
  client.println("                 /___\\/_\\/___\\");
  client.println("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-");
  client.flush();
}

// Rabbit congratulations
void showFinalRabbit(WiFiClient& client, String name, String secret) {
  client.println();
  client.println("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-");
  client.println("                  ___     ___");
  client.println("                 /   \\   /   \\       ___________________________");
  client.println("                /   / \\_/ \\   \\     /      CONGRATULATIONS,     \\");
  client.println("                \\__/\\     /\\__/    /  " + name +"!  \\");
  client.println("                     \\o O/         \\ YOUR SECRET NAME: " + secret + " /");
  client.println("                  ___/ ^ \\___      / _____________________________/");
  client.println("                     \\___/        /_/");
  client.println("                     _/ \\_");
  client.println("                    //   \\\\");
  client.println("                    |\\/_\\/|");
  client.println("                   / /   \\ \\");
  client.println("                   \\/     \\/");
  client.println("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-");
  client.flush();
}

#endif