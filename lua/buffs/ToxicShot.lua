local timePassedTotal = 0

function onUpdate(diff)



timePassedTotal = timePassedTotal+tonumber(diff)
if(timePassedTotal >= 1000000) then --every 1 second do dmg
print("Timepassed more than 10000")
timePassedTotal = 0
dealMagicDamage(getAttachedUnit(), 6) --todo proper damage.
end


end