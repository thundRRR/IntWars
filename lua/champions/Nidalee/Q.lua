Vector2 = require 'Vector2' -- include 2d vector lib 

function finishCasting()
    local current = Vector2:new(getOwnerX(), getOwnerY())
    local to = Vector2:new(getSpellToX(), getSpellToY())

    to:sub(current)
    to:normalize()

    local range = Vector2:Mult(to, 1500)
    local trueCoords = Vector2:Add(current, range)

    addProjectile(trueCoords.x, trueCoords.y)
end

function applyEffects()
   print("hit")
   if getSide(getTarget()) == getSide(getOwner()) or isDead(getTarget()) then
      return;
   end
   
   dealMagicalDamage(getEffectValue(0))
   
   -- TODO this can be fetched from projectile inibin "HitEffectName"
   addParticleTarget("Ezreal_mysticshot_tar.troy", getTarget())
   
   destroyProjectile()
end