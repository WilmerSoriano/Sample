package library;


import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.time.Duration;

 /**
   * A library video that can be checked out by a patron.
   *
   * @author             Wilmer Soriano
   * @version            1.0
   * @since              1.0
   * @license.agreement  Gnu General Public License 3.0
   */
public class Video extends Publication
{
   private Duration runtime;
   
 /**
   * checks user input and inherits Publication
   * goes into the super (aka the Publication file and save video INPUT found...)
   * 
   * The runtime is in minutes
   *
   * @param title        the name of the video
   * @param author       the principal creator of this video, typically the producer
   * @param copyright    the year in which this video was released or registered
   * @param runtime      the number of minutes required to play the video at standard speed
   * @since              1.0
   * @throws             InvalidRuntimeException
   */
   public Video(String title, String author, int copyright, int runtime)
   {
      super(title, author, copyright); /*MUST be FIRST*/

      InvalidRuntimeException Invalid = new InvalidRuntimeException(title, runtime);/*first save's the title & runtime.. more on this later for errors*/
      
      if(runtime <= 0) 
      {
         throw Invalid;
      }
      else
      {
         this.runtime = Duration.ofMinutes(runtime); /*This is import, it converts minute into a redeable hour and min string*/
      }
   }
   
 /**
   * Creates a Video instance from a BufferedReader stream.
   *
   * See {@link #save(BufferedWriter)} for the expected data format.
   *
   * @param br     a stream positioned where {@link #save(BufferedWriter)} wrote
   * @since        1.2
   */
   public Video(BufferedReader br)throws IOException
   {
      super(br);
      this.runtime = Duration.ofMinutes(Integer.parseInt(br.readLine()));
   }

 /**
   * Saves all inherited and local fields to the BufferedWriter stream.
   *
   * See {@link Publication#save(BufferedWriter)} for the expected data format
   * of the superclass fields. After the superclass fields are written
   * to the stream, the runtime field is written on a separate line in minutes.
   *
   * @param bw    the stream to which all fields will be written
   * @since      1.2
   */
   public void save(BufferedWriter bw)throws IOException
   {
      super.save(bw);
      bw.write("" + runtime.toMinutes() +'\n');
   }   
   
   /**
     * Formats the video in publication form.
     * convert everything 'aka runtime' into string
     * send it to inheritance 'Publication' inside of toStringBuilder Method.
     *
     * @returns     the result in video format(the string representation of the publication)
     * @since       1.0
     */
   @Override
   public String toString()
   {
      String time = ", The runtime is " + runtime + "minutes\n";
      return super.toStringBuilder("Video:", time); 
   }

 /**
   * Used to create our own version error exception.
   * When video runtime is Invalid.
   * 
   * @param message      the detailed message
   * @param title        the name of the library
   * @param runtime      the (invalid) number of minutes require to play the video at standard speed
   * @since              1.0
   */
   public class InvalidRuntimeException extends ArithmeticException // If everything fails send it here
   {
      public InvalidRuntimeException()
      {
         super();
      }
      
      public InvalidRuntimeException(String message)// made our own version of error to catch user input
      {
         super(message);
      }
      
      public InvalidRuntimeException(String title, int runtime) //custome error message
      {
         super(title + " has invalid runtime of " + runtime);
      }
   }
}