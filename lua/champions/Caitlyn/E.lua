Vector2 = require 'Vector2' -- include 2d vector lib 

function finishCasting()
    local current = Vector2:new(getOwnerX(), getOwnerY())
    local to = Vector2:new(getSpellToX(), getSpellToY())

    to:sub(current)
    to:normalize()

    local teleportTo = Vector2:new(to.x)
    teleportTo:mul(400)

    local trueCoords = Vector2:new(teleportTo.x, teleportTo.y)
    trueCoords:add(current)

    teleportTo(trueCoords.x, trueCoords.y)
    addProjectile(getSpellToX(), getSpellToY())
end

function applyEffects()
    --todo slow and damage enemy
end
