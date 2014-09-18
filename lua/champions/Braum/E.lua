function finishCasting()
   local duration = 2.75 + getSpellLevel()*0.25
   print("Speed increase 10")
   local buff = Buff.new("", duration, BUFFTYPE_TEMPORARY, getOwner())
   buff:setMovementSpeedPercentModifier(10)
   addBuff(buff)
end

function applyEffects()

end
