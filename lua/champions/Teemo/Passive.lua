function onUpdate(diff)
--print("Onupdate")
end

function onDamageTaken(attacker, damage, dmgType, source) --todo add callbacks for these 
print("Damage taken is ".. damage)
end

function onAutoAttack(us, target)
print("We just auto attacked!")



end