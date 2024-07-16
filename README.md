[<img src="https://assets.signaloid.io/add-to-signaloid-cloud-logo-dark-v6.png#gh-dark-mode-only" alt="[Add to signaloid.io]" height="30">](https://signaloid.io/repositories?connect=https://github.com/signaloid/Signaloid-Demo-General-C#gh-dark-mode-only)
[<img src="https://assets.signaloid.io/add-to-signaloid-cloud-logo-light-v6.png#gh-light-mode-only" alt="[Add to signaloid.io]" height="30">](https://signaloid.io/repositories?connect=https://github.com/signaloid/Signaloid-Demo-General-C#gh-light-mode-only)

# Lift force for an airfoil with uncertainties on the Signaloid platform
This program determines the lift force for an airfoil based on the Bernoulli equation and depends on the aircraft sensor measurements, the shape of the airfoil (wing) and on the wind conditions. It determines the lift force together with the uncertainties using the Signaloid Cloud Developer Platform.

## Physical principle
1. [Fork](https://docs.github.com/en/get-started/quickstart/fork-a-repo) this repository.
2. Edit `README.md` to [adapt the “Add to signaloid.io” button's URL](#option-1--using-the-add-to-signaloidio-button).
3. Edit the code and [configure the build](#configuring-the-build-configmk).



## Directory structure
The files are located in the `src/` folder for the repository, containing one C source file (`main.c`) and a `config.mk` to modify the build parameters.
```
src/
├── config.mk
└── main.c
```

## 🍰 Accessing Your GitHub Repository from the Signaloid Cloud Developer Platform
There are two ways to access a GitHub repository from the Signaloid Cloud Developer Platform.


The text you need to change is (replacing the text `<your repository URL here>`):
```html
[<img src="https://assets.signaloid.io/add-to-signaloid-cloud-logo-dark-v6.svg#gh-dark-mode-only" alt="[Add to signaloid.io]" height="30">](https://signaloid.io/repositories?connect=<your repository URL here>#gh-dark-mode-only)
[<img src="https://assets.signaloid.io/add-to-signaloid-cloud-logo-light-v6.svg#gh-light-mode-only" alt="[Add to signaloid.io]" height="30">](https://signaloid.io/repositories?connect=<your repository URL here>#gh-light-mode-only)
```

Next, go to the repository's Github page and click on the “Add to signaloid.io” button.
### Implementation
The program is implemented in C. The uncertainties in the measurements of the variables are taken into account using the `UxHw` library implemented in the `uxhw.h` header file.
### Numerical values and uncertainties
