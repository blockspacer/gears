prototypes = {
    dwarfking = {
        type = "unit",
        name = "Dwarven King",
        body = {w = 16, h = 16},
        texture = "res/img/DwarvenKing.png",
        maxHealth = 100,
        equipment = {
            head = "DwarvenCrown"
        },
        inventory = {
            size = 4,
            contents = {
                [0] = "GoldBar"
            }
        },
        selectable = true
    },
    dwarf = {
        type = "unit",
        name = "Dwarf",
        body = {w = 16, h = 16},
        texture = "res/img/Dwarf.png",
        maxHealth = 100,
        equipment = {
            hand = "Pickaxe"
        },
        inventory = {
            size = 4,
            contents = {}
        },
        selectable = true
    }
}
