
enum channel_state{
    FREE,
    EXITING,
    CAN_READ,
    CAN_WRITE
};

struct channel{
    struct proc* p;

    struct spinlock lock;

    void* read_chan;
    void* write_chan;

    enum channel_state state;

    int data;

    int counter; //counts the number of proccesses currentley using channel
};

//Assignment 2
extern struct channel channels[NCHANNELS];