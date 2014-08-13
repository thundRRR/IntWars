Vector2 = require 'Vector2' -- include 2d vector lib 

function finishCasting()
   local amt = (10 + ((getSpellLevel()-1)* 4)) * 2
   print("Speed increase" ..amt)
   addMovementSpeedBuff(getOwner(), amt, 3)
end

function applyEffects()

end