Vector2 = require 'Vector2' -- include 2d vector lib 

function finishCasting()
    local current = Vector2:new(getOwnerX(), getOwnerY())
    local to = Vector2:new(getSpellToX(), getSpellToY())

    to:sub(current)
    local trueCoords

    if(to:length() > 475) then

        to:normalize()
        local range = Vector2:Mult(to,475)
        trueCoords = Vector2:Add(current, range)
    else
        trueCoords = Vector2:new(getSpellToX(), getSpellToY())
    end

    addParticle("Ezreal_arcaneshift_cas.troy", getOwnerX(), getOwnerY());
    teleportTo(trueCoords.x, trueCoords.y)
    addParticleUnit("Ezreal_arcaneshift_flash.troy", getOwner());
    
    print("Ezreal E used from Lua, teleporting to " ..trueCoords.x .. " " .. trueCoords.y)
end

function applyEffects()

end