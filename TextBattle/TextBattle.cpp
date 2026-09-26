// TextBattle.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cassert>
#include <string>

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

int main()
{
    Weapon Sword(1, "Sword", 100, DamageType::Fire);
    Sword.GetWeaponDamageType();
    RunTests();
    std::cout << "Tests passed\n";
    return 0;
}