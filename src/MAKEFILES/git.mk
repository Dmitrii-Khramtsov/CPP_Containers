
GITBRANCH=$(shell git rev-parse --abbrev-ref HEAD)

# автоматическая заливка на гит-репозиторий с автоматическим коммитом по текущей дате и времени
push: clean removecash
	git add .; sleep 1
	@git commit -m "======= $(GITBRANCH) === $(shell date +'ДАТА %d-%m-%y === ВРЕМЯ %H:%M:%S') ======="; sleep 1
	git push origin $(GITBRANCH)

# автоматическая загрузка с гит-репозитория на текущую машину
pull: removecash
	git stash
	git pull origin $(GITBRANCH)
