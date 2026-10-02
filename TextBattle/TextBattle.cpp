// TextBattle.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cassert>
#include <string>
#include "TextBattle.h"

enum class DamageType { Physical, Fire, Poison };

// A weapon the character can equip. Immutable after creation.
class Weapon {

public: 
    // InID - Unique across all weapons; InDamage - Base damage, expected >= 0;
    Weapon(int InID, std::string InName, int InDamage, DamageType InDamageType) 
    : ID(InID), Name(InName), Damage(InDamage), Type(InDamageType)
    {
    }
    
    // Return weapon ID
    int GetWeaponID() const {
        return ID;
    }

    // Return weapon Damage
    int GetDamage() const {
        return Damage;
    }

    // Return weapon Name
    std::string GetWeaponName() const {
        return Name;
    }

    // Return weapon Damage Type
    DamageType GetWeaponDamageType() const {
        return Type;
    }

private:
    const int ID;
    std::string Name;
    int Damage = 0;
    DamageType Type;
};

// 
class Character {

public:

    Character(std::string InName, int InMaxHealth)
        : Name(InName), MaxHealth(InMaxHealth)
    {
        Health = MaxHealth;
    }

    int GetHealth() const 
    {
        return Health;
    }
    
    bool IsAlive() const {
        return Health > 0;
    }


    int GetDamage() const
    {
        return BaseDamage;
    }

    int TakeDamage(int Amount)
    {
        if (Amount <= 0) {
            return 0;
        }

        int HealthBefore = Health;
        Health -= Amount;
        if (Health < 0) {
            Health = 0;
        
        }
        return HealthBefore - Health;  
    }


    void Equip()
    {
        return;
    }
private:
    std::string Name;
    int Health = 0;
    int MaxHealth = 0;
    int BaseDamage = 0;
    Weapon* EquippedWeapon = nullptr;
};

void RunTests()
{
    Weapon Sword(1, "Sword", 100, DamageType::Fire);
    Weapon Axe(2, "Poison Axe", 250, DamageType::Poison);
    assert(Sword.GetWeaponID() == 1);
    assert(Sword.GetDamage() == 100);
    assert(Sword.GetWeaponName() == "Sword");
    assert(Sword.GetWeaponDamageType() == DamageType::Fire);
    assert(Axe.GetWeaponDamageType() == DamageType::Poison);
}

// Character Tests

void TestCharacter_StartsWithFullHealth()
{
    // New character has 100 health and alive
    Character Player("Player", 100);
    assert(Player.GetHealth() == 100);
    assert(Player.IsAlive() == true);
}

void TestCharacter_TakeDamageReturnsDamageTaken()
{
    Character Player("Player", 100);
    assert(Player.TakeDamage(30) == 30);
}



void TestCharacter()
{
    TestCharacter_StartsWithFullHealth();
    TestCharacter_TakeDamageReturnsDamageTaken();

    /*
    

    // Player with health 10 recieve damage 50, health 0 and play dead
    Character Player1("Player", 10);
    assert(Player.GetHealth() == 0);
    assert(Player.isAlive() == false);
    assert(Player.TakeDamage(50) == 10);

    // Player with health 0 is dead, with health 1 is alive
    Character Player2("Player", 1);
    assert(Player2.isAlive() == true);
    Character Player3("Player", 0);
    assert(Player3.isAlive() == false);

    //With negative or zero damage health is not reduced
    Character Player4("Player", 50);
    Player4.TakeDamage(0);
    assert(Player4.GetHealth() == 50);
    Player4.TakeDamage(-20);
    assert(Player4.GetHealth() == 50);

    // Player without weapon have base damage, with equiped weapon basedamage + weapon damage
    int test_basedamage = 10;
    Character Player4("Player", 100);
    assert(Player4.GetDamage() == test_basedamage);
    */
}

int main()
{
    TestCharacter();
    Weapon Sword(1, "Sword", 100, DamageType::Fire);
    Sword.GetWeaponDamageType();
    RunTests();
    std::cout << "Tests passed\n";
    return 0;
}