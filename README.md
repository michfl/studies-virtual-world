# Virtual world - console game

## About:
- Simple turn-based console game created as a project for Object Oriented Programming course.
- Each entity has its own set of possible actions each turn with a human being controlled by the player.
- Possible actions are moving, breeding, spreading, attacking, eating.
- Entities consist of plants and animals.

## Starting game:
- Player can start a new game and set gameboard dimnensions or load previously saved game.

## Animals (strength/initiative):
- [W] Wolf (9/5)
- [O] Sheep (5/4)
- [L] Fox (3/7) -> never moves on a field occupied by a stronger entity
- [Z] Turtle (2/1) -> has 25% chance of moving, fends off attacks of entities with strength less than 5
- [A] Antelope (4/4) -> moves two fields in one turn, 50% chance to avoid fight - moves to an unoccupied field next by
- [C] Cyber-sheep (11/4) -> each turn moves in the direction of Sosnowsky's hogweed and eats it
- [@] Human -> controlled by the player

## Plants:
- [T] Grass
- [M] Sow-thistle -> tries to spread three times in one turn
- [G] Guarana -> gives animal who ate it +3 strength
- [J] Belladonna -> kills animals that ate it
- [B] Sosnowsky's hogweed -> kills every animal in the vacinity of one field, only Cyber-sheep is resistant
