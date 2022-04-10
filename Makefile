.PHONY: exe
exe:
	make -C compiler

.PHONY: ubuntu
ubuntu:
	cd compiler && ./runmake_ubuntu.sh

.PHONY: fedora
fedora:
	cd compiler && ./runmake_fedora.sh

.PHONY: test
test:
	cd tests && python3 ifcc-test.py testfiles/

.PHONY: clean
clean:
	make -C compiler clean
	cd tests && rm -r ifcc-test-output