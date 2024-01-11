# include <playLoopFSM.h>

StateMachine::StateMachine(){
    currentState = S_STOP;
    timeval tv;
    tv.tv_sec=tv.tv_usec=0;  
    setData(tv,tv,-1,0,false,false);
}


int StateMachine::getCurrentState(){
    return currentState;
}   

void StateMachine::handle_event(Event cmd){
    if (TransitionTable[currentState][static_cast<int>(cmd)]==CANNOT_HAPPEN){
        cerr<<"Invalid Transition"<<endl;
    }
    else if(TransitionTable[currentState][static_cast<int>(cmd)]!=EVENT_IGNORE){
        currentState=TransitionTable[currentState][static_cast<int>(cmd)];
        (this->*ST_func[currentState])(); 
        (this->*ACT_func[cmd])();// if cmd==RESUME 
    }
    return;
}

void StateMachine::setState(int nextState){
    currentState=nextState;
    return;
}

void StateMachine::ST_Play() {
    std::cout << "In state PLAY\n";
}

void StateMachine::ST_Pause() {
    std::cout << "In state PAUSE\n";
}

void StateMachine::ST_Stop() {
    std::cout << "In state STOP\n";
}

// Exit functions
void StateMachine::EX_Play() {
    std::cout << "Exiting state PLAY\n";
}

void StateMachine::EX_Pause() {
    std::cout << "Exiting state PAUSE\n";
}

void StateMachine::EX_Stop() {
    std::cout << "Exiting state STOP\n";
}

// Entry functions
void StateMachine::EN_Play() {
    std::cout << "Entering state PLAY\n";
}

void StateMachine::EN_Pause() {
    std::cout << "Entering state PAUSE\n";
}

void StateMachine::EN_Stop() {
    std::cout << "Entering state STOP\n";
}

void StateMachine::ACT_Play() {
    std::cout << "Action: Play\n";

}
const std::vector<std::string> split(const std::string &str, const std::string &pattern) {
    std::vector<std::string> result;
    std::string::size_type begin, end;

    end = str.find(pattern);
    begin = 0;

    while (end != std::string::npos) {
        if (end - begin != 0) {
            result.push_back(str.substr(begin, end - begin));
        }
        begin = end + pattern.size();
        end = str.find(pattern, begin);
    }

    if (begin != str.length()) {
        result.push_back(str.substr(begin));
    }
    return result;
}


int parse_command(StateMachine* fsm,std::string str) {
    if (str.length() == 1) return -1;
    std::vector<std::string> cmd = split(str, " ");
    string cmds[3]= {"play", "pause", "stop"};
    int cmd_recv=-1;
    long startusec=0;
    for (int i = 0; i < 3; i++) {
        if (cmd[0] == cmds[i]) {
            if (i == PLAY) {
            fsm->data.delayTime=0;
            gettimeofday(&fsm->data.baseTime, NULL);//for delay display
            if(fsm->getCurrentState()==S_PAUSE && cmd[1]=="0"&& cmd[2] == "-1" && cmd[4] == "0"){
                write_fifo(true);
                cmd_recv=RESUME;
                fsm->handle_event(static_cast<Event>(cmd_recv));
                return cmd_recv;
            }
            else if (cmd.size() >= 3 && cmd[cmd.size() - 2] == "-d") {
                fsm->data.delayTime = std::stoi(cmd[cmd.size() - 1]);
                if (cmd.size() > 3) {
                    startusec = std::stoi(cmd[1]);
                }
                if (cmd.size() > 4) {
                    fsm->data.stopTime = std::stoi(cmd[2]);
                    fsm->data.stopTimeAssigned = true;
                }
            } else {
                if (cmd.size()>1) {
                    startusec = std::stoi(cmd[1]);
                }
                if (cmd.size() > 2) {
                    fsm->data.stopTime = std::stoi(cmd[2]);
                    fsm->data.stopTimeAssigned = true;
                }
            }
            fsm->data.playedTime.tv_sec = startusec / 1000000;
            fsm->data.playedTime.tv_usec = startusec % 1000000;
            }
            cmd_recv=i;
            write_fifo(true);
            fsm->handle_event(static_cast<Event>(cmd_recv));
        }
    }
}

