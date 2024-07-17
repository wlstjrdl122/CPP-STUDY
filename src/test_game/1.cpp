/*
카드 객체
   이름 (리터럴)
   대미지 (x~x까지의 상수)
   방어력 (x~x까지의 상수)
   사용 코스트 (x 상수)
   상성   (리터럴)
   능력 1, 2, 3   (플레이어의 코스트를 2 늘린다, 플레이어의 체력을 3 늘린다, 상대에게 2턴에 걸쳐 10 대미지를 입힌다 등)

플레이어 객체
    체력  (x 상수)
    카드  (기본 카드 + 지금까지 얻은 카드들)
    총 코스트 (x 상수)

상대 객체
    이름 (상대의 원래 이름)
    코드 (상대를 상징하는 코드, 플레이어가 한 번 클리어하기 전까지는 코드로 보임.)
    카드 (상대의 능력에 맞는 상대만이 가지고 있는 카드들)
    상성 (리터럴)
    총 코스트 (x 상수)
    체력 (x 상수)
    능력1, 2, 3 (매 턴 체력이 1씩 증가한다 등)
    지급 카드1, 2, 3 (상대가 플레이어에게 진다면, 플레이어에게 지급하는 카드 3개 중 하나를 랜덤으로 지급, 한 번 지급한 건 다시 지급하지 않는다.)
    능력1, 2, 3 표시 여부 (boolen 상대의 카드의 상성애 멎개 플레이어가 공격을 한다면, 해당 카드에 대응되는 상대의 능력들을 플레이어가 볼 수 있음)
*/

#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <algorithm>

/** 이름, 대미지, 방어력, 코스트, 상성, 능력*/
class Card
{
public:
  std::string name;
  int damage;
  int defense;
  int cost;
  std::string affinity;
  std::vector<std::string> abilities;

  Card(std::string n, int dmg, int def, int c, std::string aff, std::vector<std::string> ab)
      : name(n), damage(dmg), defense(def), cost(c), affinity(aff), abilities(ab) {}
};

/** health, 보유 카드, total cost*/
class Player
{
public:
  int health;
  std::vector<Card> cards;
  int totalCost;

  Player(int h, std::vector<Card> c, int tc)
      : health(h), cards(c), totalCost(tc) {}
};

/** 이름, 코드, 보유 카드, 상성, 총 코스트, 체력, 능력, 보상 카드, 능력 표시 여부*/
class Opponent
{
public:
  std::string name;
  std::string code;
  std::vector<Card> cards;
  std::string affinity;
  int totalCost;
  int health;
  std::vector<std::string> abilities;
  std::vector<Card> rewardCards;
  std::vector<bool> abilityVisibility;

  Opponent(std::string n, std::string c, std::vector<Card> cd, std::string aff, int tc, int h, std::vector<std::string> ab, std::vector<Card> rc, std::vector<bool> av)
      : name(n), code(c), cards(cd), affinity(aff), totalCost(tc), health(h), abilities(ab), rewardCards(rc), abilityVisibility(av) {}
};

void printPlayerStatus(const Player &player)
{
  std::cout << "\n\n플레이어 상태:\n";
  std::cout << "체력: " << player.health << "\n";
  std::cout << "총 코스트: " << player.totalCost << "\n";
  std::cout << "\n보유 카드:\n";
  for (const auto &card : player.cards)
  {
    std::cout << "  이름: " << card.name << ", 대미지: " << card.damage
              << ", 방어력: " << card.defense << ", 코스트: " << card.cost
              << ", 상성: " << card.affinity << "\n";
    std::cout << "  능력: ";
    for (const auto &ability : card.abilities)
    {
      std::cout << ability << " ";
    }
    std::cout << "\n\n";
  }
}

void printOpponentStatus(const Opponent &opponent)
{
  std::cout << "\n\n상대 상태:\n";
  std::cout << "이름: " << opponent.name << "\n";
  std::cout << "코드: " << opponent.code << "\n";
  std::cout << "체력: " << opponent.health << "\n";
  std::cout << "총 코스트: " << opponent.totalCost << "\n";
  std::cout << "상성: " << opponent.affinity << "\n";
  std::cout << "능력: ";
  for (size_t i = 0; i < opponent.abilities.size(); ++i)
  {
    if (opponent.abilityVisibility[i])
    {
      std::cout << opponent.abilities[i] << " ";
    }
  }
  std::cout << "\n보유 카드:\n";
  for (const auto &card : opponent.cards)
  {
    std::cout << "  이름: " << card.name << ", 대미지: " << card.damage
              << ", 방어력: " << card.defense << ", 코스트: " << card.cost
              << ", 상성: " << card.affinity << "\n";
    std::cout << "  능력: ";
    for (const auto &ability : card.abilities)
    {
      std::cout << ability << " ";
    }
    std::cout << "\n\n";
  }
  std::cout << "보상 카드:\n";
  for (const auto &card : opponent.rewardCards)
  {
    std::cout << "  이름: " << card.name << ", 대미지: " << card.damage
              << ", 방어력: " << card.defense << ", 코스트: " << card.cost
              << ", 상성: " << card.affinity << "\n";
    std::cout << "  능력: ";
    for (const auto &ability : card.abilities)
    {
      std::cout << ability << " ";
    }
    std::cout << "\n\n";
  }
}

int main()
{
  srand((unsigned)time(0));

  Card basicCard("기본 카드", 5, 3, 1, "None", {"플레이어 코스트 2 상승"});
  Card basicCard2("기본 카드2", 30, 2, 2, "None", {"상대의 코스트 1 하락"});
  Card rewardCard1("테스트_보상카드1", 10, 5, 2, "Fire", {"플레이어 체력 3 회복"});
  Card rewardCard2("테스트_보상카드2", 8, 4, 2, "Water", {"2턴에 걸쳐 10 데미지"});
  Card rewardCard3("테스트_보상카드3", 6, 6, 1, "Earth", {"방어력2 감소"});

  Player player(100, {basicCard, basicCard2}, 10);

  Opponent opponent1("테스트상대1", "테스트상대1 코드 & 요약", {basicCard}, "Fire", 12, 100, {"매 턴 체력 1 회복"}, {rewardCard1, rewardCard2, rewardCard3}, {true, false, true});

  Opponent opponent2("테스트상대2", "테스트상대2 코드 & 요약", {basicCard}, "Water", 14, 120, {"매 턴 2 데미지 --"}, {rewardCard1, rewardCard2, rewardCard3}, {true, true, false});

  Opponent opponent3("테스트상대3", "테스트상대3 코드 & 요약", {basicCard}, "Earth", 16, 150, {"능력333"}, {rewardCard1, rewardCard2, rewardCard3}, {false, true, true});

  std::vector<Opponent> opponents = {opponent1, opponent2, opponent3};
  std::random_shuffle(opponents.begin(), opponents.end());

  std::vector<Opponent> selectedOpponents = {opponents[0], opponents[1]};

  std::cout << "\n\n두 개의 방이 보입니다:\n";
  for (int i = 0; i < selectedOpponents.size(); ++i)
  {
    std::cout << i + 1 << ". " << selectedOpponents[i].code << "\n";
  }

  int choice;
  std::cin >> choice;
  Opponent chosenOpponent = selectedOpponents[choice - 1];

  std::cout << "\n\n"
            << chosenOpponent.name << "에 진입했습니다." << "\n";

  while (player.health > 0 && chosenOpponent.health > 0)
  {
    printPlayerStatus(player);
    printOpponentStatus(chosenOpponent);
    std::cout << "___________________________________\n";
    std::cout << "\n사용 가능한 카드:\n";
    for (int i = 0; i < player.cards.size(); ++i)
    {
      std::cout << i + 1 << ". " << player.cards[i].name << " (대미지: " << player.cards[i].damage << ", 방어력: " << player.cards[i].defense << ", 코스트: " << player.cards[i].cost << ")\n";
    }

    std::cout << "카드 선택: ";
    int cardChoice;
    std::cin >> cardChoice;
    Card chosenCard = player.cards[cardChoice - 1];

    std::cout << "\n\n";

    if (player.totalCost >= chosenCard.cost)
    {
      chosenOpponent.health -= chosenCard.damage;
      player.totalCost -= chosenCard.cost;
      std::cout << chosenCard.name << "을 사용하여 " << chosenCard.damage << "의 대미지를 입혔습니다. 상대의 남은 체력: " << chosenOpponent.health << "\n";

      for (const auto &ability : chosenCard.abilities)
      {
        if (ability == "플레이어 코스트 2 상승")
        {
          player.totalCost += 2;
        }
        else if (ability == "")
        {
          /// 나중에 추가
        }
      }
    }
    else
    {
      std::cout << "코스트가 부족합니다.\n";
    }

    if (chosenOpponent.health > 0)
    {
      Card opponentCard = chosenOpponent.cards[0]; // 일단 첫번째 카드만 사용하도록, 나중에 알고리즘 만들어야

      player.health -= opponentCard.damage;
      std::cout << chosenOpponent.name << "이 " << opponentCard.name << "을 사용하여 " << opponentCard.damage << "의 대미지를 입혔습니다. 플레이어의 남은 체력: " << player.health << "\n";

      for (const auto &ability : chosenOpponent.abilities)
      {
        if (ability == "매 턴 체력 1 회복")
        {
          chosenOpponent.health += 1;
          std::cout << chosenOpponent.name << "의 체력이 1 증가했습니다. 현재 체력: " << chosenOpponent.health << "\n";
        }
        // 능력별로 추가
        // 능력 이름과 능력 코드 따로 둬서 코드 리팩토링 하는 게 좋을듯
      }
    }
  }

  if (player.health > 0)
  {
    std::cout << "승리\n";
    std::cout << "3개의 카드를 떨어뜨렸습니다. 하나를 주워주세요.\n";
    for (int i = 0; i < chosenOpponent.rewardCards.size(); ++i)
    {
      std::cout << i + 1 << ". " << chosenOpponent.rewardCards[i].name << "\n";
    }
    int rewardChoice;
    std::cin >> rewardChoice;
    player.cards.push_back(chosenOpponent.rewardCards[rewardChoice - 1]);
    std::cout << "보상 카드 " << chosenOpponent.rewardCards[rewardChoice - 1].name << "를 획득했습니다.\n";
  }
  else
  {
    std::cout << "패배\n";
  }

  return 0;
}
