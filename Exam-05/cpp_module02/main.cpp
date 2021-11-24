#include "Warlock.hpp"
#include "Dummy.hpp"
#include "Fwoosh.hpp"
#include "TargetGenerator.hpp"
#include "BrickWall.hpp"
#include "Polymorph.hpp"
#include "Fireball.hpp"
#include "SpellBook.hpp"

int main()
{
  std::cout << "--- MY TESTS ---\n";
  Warlock richard("Richard", "foo");
  richard.introduce();
  richard.setTitle("Hello, I'm Richard the Warlock!");
  richard.introduce();
  
  std::cout << "--- create targets ---\n";
  BrickWall brickwall;
  Dummy *dummy = new Dummy();

  TargetGenerator tarGen;
  tarGen.learnTargetType(&brickwall);
  tarGen.learnTargetType(dummy);

  ATarget* wall = tarGen.createTarget("Inconspicuous Red-brick Wall");
  ATarget* wall2 = tarGen.createTarget("Target Practice Dummy");

  std::cout << "--- create spells ---\n";
  Polymorph* polymorph = new Polymorph();
  Fireball* fireball = new Fireball();
  Fwoosh fwoosh;

  richard.learnSpell(polymorph);
  richard.learnSpell(fireball);
  richard.learnSpell(&fwoosh);
  richard.learnSpell(&fwoosh);

  std::cout << "--- launch ---\n";
  richard.launchSpell("Polymorph", *wall);
  richard.launchSpell("Fireball", *wall);
  richard.launchSpell("Fwoosh", *wall);

  richard.launchSpell("Polymorph", *wall2);
  richard.launchSpell("Fireball", *wall2);
  richard.launchSpell("Fwoosh", *wall2);

  richard.launchSpell("Fireball", *tarGen.createTarget("Target Practice Dummy"));

  std::cout << "--- forget spells ---\n";
  richard.forgetSpell("haha");
  richard.launchSpell("Polymorph", *wall);
  richard.forgetSpell("Polymorph");
  richard.launchSpell("Polymorph", *wall);

  std::cout << "--- fail launch ---\n";
  richard.launchSpell("lol", *wall);
  richard.launchSpell("Fireball", *tarGen.createTarget("lol"));

  std::cout << "--- deconstructos ---\n";

  delete polymorph;
  delete fireball;
  delete dummy;

  return 0;
}