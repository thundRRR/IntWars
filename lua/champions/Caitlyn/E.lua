Vector2 = require 'Vector2' -- include 2d vector lib 

function finishCasting()
    local current = Vector2:new(getOwnerX(), getOwnerY())
    local to = Vector2:new(getSpellToX(), getSpellToY())

    to:sub(current)
    to:normalize()

    local teleportTo = to.mult(-1)

    teleportTo.mult(400)

    local trueCoords = current.add(teleportTo)

    teleportTo(trueCoords.x, trueCoords.y)
    addProjectile(trueCoords.x, trueCoords.y)
end

function applyEffects()
    --todo slow and damage enemy
end