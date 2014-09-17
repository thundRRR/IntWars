function finishCasting()
   local amt = 12 + getSpellLevel()*4
   print("Speed increase" ..amt)
   local buff = Buff.new("Overdrive", 8.0, getOwner())
   buff:setMovementSpeedPercentModifier(amt)
   addBuff(buff)
end

function applyEffects()

end
