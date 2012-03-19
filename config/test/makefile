

test_config: config_test.cpp ../src/config.a
	g++ -o test_config config_test.cpp -I../src ../src/config.a -D_DEBUG

.PHONY:clean

clean:
	rm -f test_config
