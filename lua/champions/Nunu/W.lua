function finishCasting()
   local amt = 7 + getSpellLevel()
   print("Speed increase" ..amt)
   local buff = Buff.new("BloodBoil", 12.0, getOwner())
   buff:setMovementSpeedPercentModifier(amt)
   addBuff(buff)
end

function applyEffects()

end
