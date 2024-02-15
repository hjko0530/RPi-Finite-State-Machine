# include <StateMachine.h>
# include <FSM_Common.h>

extern const std::string cmds[10];
extern std::thread led_loop, of_loop;
extern Player player;
extern LEDPlayer led_player;
extern OFPlayer of_player;
extern int dancer_fd;
extern string path;
extern const char *rd_fifo;
extern const char *wr_fifo;

StateMachine::StateMachine(){
    timeval tv;
    tv.tv_sec=tv.tv_usec=0;  
    setData(tv,tv,-1,0,false,false);
    currentState = S_STOP;
}

int StateMachine::getCurrentState(){
    return currentState;
}   

void StateMachine::transition(int cmd){
    if (TransitionTable[currentState][cmd]==CANNOT_HAPPEN){
        fprintf(stderr,"[FSM] CANNOT HAPPEN\n");
    }
    else if(TransitionTable[currentState][cmd]!=EVENT_IGNORE){
        fprintf(stderr,"[FSM]currentState:%d\n",currentState);
	    (this->*EX_func[currentState])();
        currentState=TransitionTable[currentState][cmd];
	    fprintf(stderr,"[FSM]nextState: %d\n",currentState);
        (this->*EN_func[currentState])();
    }
    else{
    	fprintf(stderr,"[FSM]EVENT IGNORE\n";);
    }
    return;
}

void StateMachine::ST_Play() {      //check if it's times up
    timeval tv;
    tv = getCalculatedTime(data.baseTime);  
    long played_us = tv.tv_sec * 1000000 + tv.tv_usec;
    played_us/=1000;	   
    if (played_us > this->data.stopTime && this->data.stopTime != -1) {
        (this->*EX_func[currentState])();
        currentState= S_STOP;
        (this->*EN_func[currentState])();
    }
}

void StateMachine::ST_Pause() { 
}

void StateMachine::ST_Stop() {
}

// Exit functions
void StateMachine::EX_Play() {      //store playedTime
    this->data.playedTime = getCalculatedTime(data.baseTime);
    return;
}

void StateMachine::EX_Pause() {
    //restart();    #hjko
}

void StateMachine::EX_Stop() {
    restart();
    data.delayDisplay=true;
}
// Entry functions
void StateMachine::EN_Play() {
    timeval tv;    
    while (data.delayTime>0){       //delay handling, 
        timeval tv = getCalculatedTime(data.baseTime);
       	long delayed_us = tv.tv_sec * 1000000 + tv.tv_usec;
	    delayed_us/=1000;
        of_player.delayDisplay(&data.delayDisplay);
        led_player.delayDisplay(&data.delayDisplay);
        if (delayed_us > data.delayTime / 5l&&data.delayDisplay){
	    data.delayDisplay = false;
	    }
        if (delayed_us > data.delayTime) {
            fprintf(stderr,"[FSM]delay finished, delayTime:%f\n",data.delayTime/1000000l);
            break;
        }
    }
    data.delayTime=0;
    data.baseTime = getCalculatedTime(data.playedTime);
    fprintf(stderr, "[FSM]startTime:%f\n", (data.playedTime.tv_sec + data.playedTime.tv_usec/1000000l));
    resume(this);
}

void StateMachine::EN_Pause() {  
    //releaseLock(dancer_fd, path.c_str());     #hjko
}

void StateMachine::EN_Stop() {
    //led_player.darkAll(); #hjko
    led_player.controller.finish();
    //of_player.darkAll(); #hjko
    releaseLock(dancer_fd, path.c_str());
    data.stopTimeAssigned = data.delayDisplay = false;
    data.stopTime = -1;
}


timeval StateMachine::getPlayedTime() {
    timeval tv = getCalculatedTime(data.baseTime);
    data.playedTime=tv;
    return tv;
}

void StateMachine::setData(timeval _baseTime, timeval _playedTime, long _stopTime, long _delayTime, bool _stopTimeAssigned, bool _isLiveEditting){
    //for initialization
    data.baseTime = _baseTime;
    data.playedTime = _playedTime;
    data.stopTime = _stopTime;
    data.delayTime = _delayTime;
    data.delayDisplay=false;
    data.stopTimeAssigned = _stopTimeAssigned;
    data.isLiveEditting = _isLiveEditting;
}

