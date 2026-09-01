
class enum unitID {
AC_Unit=0x1B6U,
BCM_Unit=0x7DF,
};
//CRTP 
 template <typename T>
 class  Singleton
 {

 public:
 static T& Instance(){
  static T singleInctance;
  return singleInctance;

  Singleton(const Singleton&) = delete;
  Singleton& operator=(const Singleton&) = delete;
  protected:
  Singleton() {};
 };


class CanManagement { 
  public:
    virtual ~CanManagement() {}
    virtual const uint32_t getID() const = 0;
    virtual const uint32_t getDLC() const = 0;
    virtual const uint32_t getPeriod() const = 0;
    virtual Error_t getError() const = 0;
}
class CAN_ACManagement :  public CanManagement , public Singleton<CAN_ACManagement> {
  protected:
  private:
    CAN_ACManagement() : current_id(0x1B6), dlc(8), period(100) {}
    uint32_t current_id;
    uint32_t dlc;
    uint32_t period;

  public:
    friend class Singleton<CAN_ACManagement>;
  
    const uint32_t getID() const override { return current_id; }
    const uint32_t getDLC() const override { return dlc; }
    const uint32_t getPeriod() const override { return period; }
    Error_t getError() const override { return Error_t::SUCCESS; }

    ACRequest getACWorkRequest() const;
    Error_t   getAC_BusVoltage(uint16_t voltage)const;
		Error_t   getAC_BusCurrent(float current) const;
		Error_t   getAC_phaseCurrent(float current) const;
		Error_t   getAC_Speed(uint16_t speed) const; // RPM
		Error_t   getAC_Temperature(int16_t Temperatur) const;
 
}

class CAN_‌BCMManagement :  public CanManagement , public Singleton<CAN_ACManagement> {
   private:
    CAN_BCMManagement() : current_id(0xDEE), dlc(8), period(50) {}
    uint32_t current_id;
    uint32_t dlc;
    uint32_t period;
  public:
    friend class Singleton<CAN_ACManagement>;
  
   const uint32_t getID() const override {  return current_id; }
    const uint32_t getDLC() const override { return dlc; }
    const uint32_t getPeriod() const override { return period; }
    Error_t getError() const override { return Error_t::SUCCESS; }
   
    uint64_t getBCM_ParameterRequest() const;
	  uint8_t getBCM_Ack() const;
 
}


class CANStrategy public Singleton<CANStrategy>,public CANFrame, public CANCommunication
{
friend class Singleton<CANStrategy>;
private:
  CANStrategy();
public:
std::mutex
 std::map<uint32_t, CANFrame*> strategyMap;
 strategyMap[static_cast<uint32_t>(unitID::AC_Unit)] = &CAN_‌BCMManagement::Instance();
 strategyMap[static_cast<uint32_t>(unitID::BCM_Unit)]= &CAN_ACManagement::Instance();
 
  void &selectUnit( unitID unitName ){
    return & strategyMap static_cast<uint32_t>(unitName)>;
  }
    
};


