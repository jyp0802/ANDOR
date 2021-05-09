# Hierarchical AND/OR Graph

This is the repository for Hierarchical AND/OR grapph, which can be employed as a *Task Representation* module.
It semantically formalizes a process between operators (humans and/or robots).
Using that, you can a easily represent a custom task to follow.
This module is developed mainly for represeting the human or robot tasks, but it is not limited to that. The user can easily embed the AND/OR graph in any middleware; in our case we develop it as a [ROS](http://www.ros.org/) package with a service-client paradigm.

# Contents
 - [:orange_book: The general idea](#orange_book-the-general-idea)
 - [:hammer: Dependencies and build](#hammer-dependencies-and-build)
 - [:running: Using the software](#running-using-the-software)
 - [:nerd_face: Mantainers](#nerd_face-mantainers)
 - [:page_facing_up: References](#page_facing_up-references)
 - [:information_source: Further information](information-source-further-information)
 - [:unlock: License](#unlock-license)

# :orange_book: The general idea


An AND/OR graph *G(N,H)* consists of a set of nodes *N* and a set of hyper-arcs *H*. A node *n ∈ N* represents a *state* of the cooperation, whereas a hyper-arc *h ∈ H* represents a specific *state transition* among states. In particular, a hyper-arc *h* connects a set of *child* nodes *N<sub>C</sub> ⊆ N* to a *parent* node *n<sub>P</sub> ∈ N*.
The relation between child nodes in a hyper-arc is the logic AND, while the relation between different hyper-arcs inducing on the same parent node is the logic OR.
Each hyper-arc *h ∈ H* corresponds to a sequence of ordered actions, *A(h)*, to be executed by the human operator or the robot to reach the cooperation status described by the parent node.


# :hammer: Dependencies and build
The only dependency is [ROS](http://www.ros.org/) and you can download it from [here](http://www.ros.org/install/).

After installing ros, using git, clone the repo in your `src` directory of your ros workspace, or download the repo and extract it in `src` directory of your ros workspace.

```
cd <path to your ros workspace>
catkin_make
```

# :running: Using the software

To write an AND/OR graph description, please follow the instructions provided [here](./docs/Instructions.md).

To run the AND/OR graph (as a service) run the following command:
```
rosrun andor andor
```
To run the example (as a client) run the following command:
```
rosrun andor example
```


You can generate [doxygen](http://www.doxygen.nl/) documentation using follwoing command:
```
cd <path to your ros workspace>/src/andor

doxygen doxygen_config
```

# :nerd_face: Mantainers
If you have any question regarding the implementation, you can open an issue in the repo and CC the maintainer or contact directly the maintainer.

* [Kourosh Darvish](https://github.com/kouroshD)

:email: kourosh.darvish@gmail.com

# :page_facing_up: References
If you're going to use this package for your work, please quote the following papers within any resulting publication:


```
K. Darvish, F. Wanderlingh, B. Bruno, E. Simetti, F. Mastrogiovanni, and G. Casalino, "Flexible human-robot cooperation models for assisted shop-floor tasks," Mechatronics, vol. 51, pp. 97–114, 2018.
```
```
K. Darvish, E. Simetti, F. Mastrogiovanni and G. Casalino, "A Hierarchical Architecture for Human–Robot Cooperation Processes," in IEEE Transactions on Robotics, vol. 37, no. 2, pp. 567-586, 2021.
```
```
@article{DARVISH2018,
title = "Flexible human–robot cooperation models for assisted shop-floor tasks",
journal = "Mechatronics",
volume = "51",
pages = "97 - 114",
year = "2018",
issn = "0957-4158",
doi = "https://doi.org/10.1016/j.mechatronics.2018.03.006",
url = "http://www.sciencedirect.com/science/article/pii/S0957415818300485",
author = "Kourosh Darvish and Francesco Wanderlingh and Barbara Bruno and Enrico Simetti and Fulvio Mastrogiovanni and Giuseppe Casalino",
}

@ARTICLE{Darvish2021,
author={Darvish, Kourosh and Simetti, Enrico and Mastrogiovanni, Fulvio and Casalino, Giuseppe},
journal={IEEE Transactions on Robotics},
title={A Hierarchical Architecture for Human–Robot Cooperation Processes},
year={2021},
volume={37},
number={2},
pages={567-586},
doi={10.1109/TRO.2020.3033715}}
```
# :information_source: Further information

For more information please contact the follwoing authors:

* [Kourosh Darvish](https://github.com/kouroshD):

:email: kourosh.darvish@edu.unige.it

* [Fulvio Mastrogiovanni](https://www.dibris.unige.it/mastrogiovanni-fulvio):

:email: fulvio.mastrogiovanni@unige.it


# :unlock: License
The license is porovided [here](./LICENSE).
