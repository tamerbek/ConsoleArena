// TextBattle.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cassert>
#include <string>
#include <cstdlib>
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

    Character(std::string InName, int InMaxHealth, int InBaseDamage)
        : Name(InName), MaxHealth(InMaxHealth)
    {
        Health = MaxHealth;
        BaseDamage = InBaseDamage;
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
        if (EquippedWeapon == nullptr) {
            return BaseDamage;
        }
        return BaseDamage + EquippedWeapon->GetDamage();
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


    void Equip(Weapon* InWeapon)
    {
        EquippedWeapon = InWeapon;

        return;
    }

    int Attack(Character& Target) {
        return Target.TakeDamage(GetDamage());
    }

    int Roll(int Min, int Max) {
        return rand() % (Max - Min + 1) + Min;
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
    Character Player("Player", 100, 5);
    assert(Player.GetHealth() == 100);
    assert(Player.IsAlive() == true);
}

void TestCharacter_TakeDamageReturnsDamageTaken()
{
    Character Player("Player", 100, 5);
    assert(Player.TakeDamage(30) == 30);
    assert(Player.GetHealth() == 70);
}

// Player with health 10 recieve damage 50, health 0 and play dead
void TestCharacter_PlayerDiesFromExcessDamage() 
{
    Character Player("Player", 10, 5);
    assert(Player.TakeDamage(50) == 10);
    assert(Player.GetHealth() == 0);
    assert(Player.IsAlive() == false);
}

// Player with health 0 is dead, with health 1 is alive
void TestCharacter_AliveAtOneHealthDeadAtZero()
{
    Character Player("Player", 1, 5);
    assert(Player.IsAlive() == true);
    Character Player1("Player", 0, 5);
    assert(Player1.IsAlive() == false);
}

//With negative or zero damage health is not reduced
void TestCharacter_IgnoresZeroAndNegativeDamage()
{ 
    Character Player("Player", 50, 5);
    Player.TakeDamage(0);
    assert(Player.GetHealth() == 50);
    Player.TakeDamage(-20);
    assert(Player.GetHealth() == 50);
}

// Player without weapon have base damage, with equiped weapon basedamage + weapon damage
void TestCharacter_BaseDamageAndDamageWithWeapon() {
    int BaseDamage = 5;
    Character Player("Player", 50, BaseDamage);
    assert(Player.GetDamage() == 5);

    Weapon Sword(1, "Sword", 100, DamageType::Fire);
    Player.Equip(&Sword);
    assert(Player.GetDamage() == 105);
}

// Test character attack
void TestCharacter_AttackDealsCorrectDamage() {
    Character Player("Player", 100, 5);
    Character NPC("NPC", 100, 3);
    assert(Player.Attack(NPC) == 5);
    assert(Player.GetHealth() == 100);
    assert(NPC.GetHealth() == 95);
}

// Test roll funcrion
void TestCharacter_RollReturnsValueWithinRange() {
    
    Character Player("Player", 100, 5);
    bool bIsEdge = false;
    for (int i = 0; i < 10000; ++i) {
        if (Player.Roll(1, 6) < 1) {
            bIsEdge = true;
        }
        
    }
    assert(bIsEdge == false);
}

void TestCharacter()
{
    TestCharacter_StartsWithFullHealth();
    TestCharacter_TakeDamageReturnsDamageTaken();
    TestCharacter_PlayerDiesFromExcessDamage();
    TestCharacter_AliveAtOneHealthDeadAtZero();
    TestCharacter_IgnoresZeroAndNegativeDamage();
    TestCharacter_BaseDamageAndDamageWithWeapon();
    TestCharacter_AttackDealsCorrectDamage();
    TestCharacter_RollReturnsValueWithinRange();

}

int main()
{
    TestCharacter();
    RunTests();
    std::cout << "Tests passed\n";
    return 0;
}