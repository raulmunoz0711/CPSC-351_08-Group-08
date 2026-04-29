# CPSC-351-Group_08

## Group Members
- Raul Munoz, raulmunoz@csu.fullerton.edu
- Calista Ruiz, calistaruiz@csu.fullerton.edu
- Erick Rayas, erickrayas@csu.fullerton.edu
- AP Calderon, calderon.antoniop410@csu.fullerton.edu
- Linh Tran, L_N_Tran@csu.fullerton.edu

## Download Required / How to Execute [Windows/Mac/Linux]
- https://code.visualstudio.com/docs/cpp/config-mingw
    - If download is followed properly on link, then you can run code on Visual Studio.

- System Check [Windows/Mac/Linux]
    - Run the following command in the terminal: gcc --version
        - If compiler installed properly then you will see current verion installed

- Compile & Execute on Terminal[Windows/Mac/Linux]:
    - Navigate to folder containing file CPSC-351-08-Group_08_Algos.c
    - Once in file run the following command
        gcc CPSC-351-08-Group_08_Algos.c -o <name you have chose>
        ./<name you have chosen>

## Storyline
- We are in an age in which video games have become commonplace for people of all ages. There are many game systems, each with unique games, allowing users to play whatever is fun for them. However, one thing all video games share is that, when playing an Online game, the user must connect to the game server to play with other online players. For our project, imagine we have just finished creating an online open-world game and must decide how users will join the servers and start playing. This is important because we are planning for this game to be a success, which means the server’s capacity will be an issue. While there are currently no plans for expansion, we want to ensure that each user understands how the game queue will work when entering the game servers.
- Players are logging into the server to play. Scheduling in this setting is important since due to the finite amount of players a server can host at a time, there’s bound to be more players than the server’s able to handle. Therefore, there must be a fair and efficient way to choose which players to let in and which to transfer to another server. For this reason, we have decided that these three options would make the most sense. First, the First Come First Serve algorithm was chosen because this is how many game servers operate today, meaning whatever user joins first gets access first. Second, Shortest Job First was considered, which admits players into the server based on how long it will take the server to fully process user information. It will admit players with the quickest execution time and ignore users who carry a large execution time. Finally, the Priority Scheduling algorithm. This means we are planning on creating a premium service that allows users to cut the line, who enter before non-premium users, getting into the server first. These algorithms highlight the different methods in which we can ensure either happiness and/or profit from users when connecting to the game server.


## Algorithms Selected
- FCFS:
    PLayers are giving access to the server based on the order in which they entered the queue.
- Shortest Job First:
    Players are let into the server in according to fastest connection.
- Prioirty Scheduling:
    Players are let in on a FCFS basis but if a player has priority status they cut to the front of the line.

## Initial Input Design
    __User__ | __Arrival__ | __Burst__ | __Priority__
    User1: 0 | 6 | 2
    User2: 1 | 3 | 2
    User3: 2 | 5 | 1
    User4: 4 | 1 | 2
    User5: 6 | 4 | 1

## Results
- FCFS:
    Average Wait Time: 6.2s | Average Turnaround Time: 10.0s | Average Completion Time: 12.6s
- Shortest Job First:
    Average Wait Time: 4.8s | Average Turnaround Time: 8.6s | Average Completion Time: 11.2s
- Priority Scheduling:
    Average Wait Time: 7.4s | Average Turnaround Time: 11.2s | Average Completion Time: 13.8s

    Even though all 3 algorithms are servicing the exact same players, the order in which the players are serviced drastically affects the spread of waiting time between users.

## Discussion
- SJF clearly is the most efficient but FCFS is the fairest algorithm. Priority scheduling really only benefits users who purchase the priority pass. However, our sample size is small compare to the thousands we expect to host in a queue, so for now SJF seems to win on every system-level metric.

    Now the question becomes:
        - Do you want your game to be fair? FCFS 
        - Do you want your game to be fast? SJF 
        - Do you want to monetize your game? Priority Scheduling
