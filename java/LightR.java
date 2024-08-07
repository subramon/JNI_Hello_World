class LightR {
  private native long init(
      String config_dir
      );
  private native int score(
      long c_address,
      String j_arg1, 
      String j_arg2 
      );
  private native int close(
      long c_address
      );
  public static void main(String args[]) {
    int status = 0;
    String x = System.getProperty("java.library.path");
    // System.out.println("java.library.path =  " + x );

    String j_arg1 = "some string argument";
    String j_arg2 = "some oher string argument";

    LightR lr = new LightR();
    long c_address = 0;

    c_address = lr.init("/home/subramon/RBC/JNI/HELLO_WORLD/lua_dir");
    if ( c_address == 0 ) { System.out.println("ERROR"); }
    System.out.println("Initialized LightR: c_address= " + c_address );

    //--------------------------------------------------
    status = lr.score(c_address, j_arg1, j_arg2);
    if ( status != 0 ) { System.out.println("ERROR"); }
    //--------------------------------------------------
    status = lr.close(c_address);
    if ( status != 0 ) { System.out.println("ERROR"); }

  }
  static {
    // Remember to set LD_LIBRARY_PATH properly
    System.loadLibrary("LightR");
  }
}
