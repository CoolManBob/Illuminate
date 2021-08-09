function::state InitialState()
	self._behaviour = (idle)
	self._action = (WAIT)
	sellf._callCycleTime = (0)
	self._exit = (Wait)
end

function::state Wait()
	local findTarget 
	self._Target =(player)
	self._distanceMin = (150)
	self._distanceMax = (500)
	local changeStateReturn
	self._state = function::movement Move_Return
	local changeStateRandom
	self._state = function::movement Move_Random
	self._dice = (50)
end

function::state Wait1()
	local changeStateChaser
	self._state = function::movement Move_Chaser
	self._distanceMin = (150)
	self._distanceMax = (500)
	local changeStateChaserSlow
	self._state = function::movement Move_Chaser_Slow
	self._distanceMin = (150)
	self._distanceMax = (500)
	local changeStateRandom
	self._state = function::movement Move_Random
	self._dice = (50)
end

function::movement Move_Chaser()
	self._behaviour = (chase)
	self._action = (RUN)
	self._callCycleTime = (500)	
	self._exit = function::movement Move_Chaser
	self._targetLost = function::movement Move_Return
	self._failFindPath = function::state Wait
	local changeStateReturn
	self._state = function::movement Move_Return
	self._origin = (800)
	local changeStateRandom
	self._state = function::movement Move_Random
	self._dice = (50)
end

function::movement Move_Chaser_Slow()

end

function::movement Move_Random()

end

function::movement Move_Return()

end