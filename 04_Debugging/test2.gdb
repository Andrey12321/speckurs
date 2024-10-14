set pagination off
set $log_index = -1
b 29
commands
	silent
	set $log_index = $log_index + 1
    
	if $log_index >= 28 && $log_index <= 35
		echo ***
		p start
		echo ***
		p end
		echo ***
		p step
		echo ***
		p i
	end
	cont
end

run
quit
