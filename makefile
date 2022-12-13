
run_backup:
	# $(foreach alpha,$(ALPHAS),\
	# 	export NUM_THREADS=8 && \
	# 	export ALPHA=$(alpha) && \
	# 	echo $$ALPHA && \
	# 	python samples/simple/mandelbrot.py;)


NUMBERS = 2 4 6 8 10 12 14 16
run:
	$(foreach num,$(NUMBERS),\
		export ALPHA=$(num) && \
		export NUM_THREADS=8 && \
		python samples/simple/mandelbrot.py;)