function::state InitialState()
	self._behaviour = (idle)
	self._action = (WAIT)
	sellf._callCycleTime = (1000)
	self._exit = (Wait)
	self._variable = (_HP)
end

function::state Wait()
	self._behaviour = (idle)
	self._action = (WAIT)
	sellf._callCycleTime = (1000)
	self._exit = (Wait)
	if self._variable = (_HP) and self._variable =< 10 function Chest_open
end

function Chest_open()
	self._behaviour = (idle)
	self._action = (END_DIE)
	sellf._callCycleTime = (1000)
	self._exit = function Suicide_Die
end

function Suicide_Die()
	self._behaviour = (dead)
	self._suicide = (false)
	self._action = (SUICIDE_DIE)
	sellf._callCycleTime = (1000)
	self._exit = (Suicide_Die)
end