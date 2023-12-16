package library;


import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.time.LocalDate;

 /**
   * To be able to publish a book or video
   * And library resource that can be checked out by a patron.
   *
   * @author      Wilmer Soriano
   * @version     1.0
   * @since       1.0
   * @license.agreement  Gnu General Public License 3.0
   */
public class Publication
{
   private String title;
   private String author;
   private int copyright;
   private String loanedTo;
   private LocalDate dueDate;


 /** Creates a publication 
   *
   * Note: The year of copyright must be between 1900 and the present.
   *
   * @param title     the name of the library
   * @param author    the principal creator of this resource
   * @param copyright the year in which this publication was released or registered
   * @since              1.0
   */
   public Publication(String title, String author, int copyright)
   {
      this.title = title;
      this.author = author;
      this.copyright = copyright;
      
      LocalDate date = LocalDate.now();
      int year = date.getYear();                                 
      
      if( copyright < 1900 || copyright > year)
      {
        throw new IllegalArgumentException("WARNING: copyright not intended before 1900's or after " + year);
      }
   }
 
 /**
   * Creates a Publication instance from a BufferedReader stream.
   *
   * See {@link #save(BufferedWriter)} for the expected data format.
   *
   * @param br     a stream positioned where {@link #save(BufferedWriter)} wrote
   * @since        1.2
   */  
   public Publication(BufferedReader br) throws IOException
   {
      this.title = br.readLine();
      this.author = br.readLine();
      this.copyright = Integer.parseInt(br.readLine());
      String check;
      check = br.readLine();
      
      if(check.equals("null"))
      {
         this.loanedTo = null;
         this.dueDate = null;
      }
      else
      {
         this.loanedTo = check;
         this.dueDate = LocalDate.of(Integer.parseInt(br.readLine()),
                                    Integer.parseInt(br.readLine()),
                                    Integer.parseInt(br.readLine()));
      }
   }

 /**
   * Saves all local fields to the BufferedWriter stream.
   *
   * The value of plain fields that are never null are written one per line. 
   * Fields which may be null are written as "null" (if null) or as "" 
   * followed by the value on the next line(s) otherwise. The values of 
   * LocalDate objects are written as 3 integers on separate lines - year, month, and date.
   *
   * @param bw    the stream to which all fields will be written
   * @since      1.2
   */
   public void save(BufferedWriter bw)throws IOException
   {
      bw.write(title + '\n');
      bw.write(author + '\n');
      bw.write("" + copyright + '\n');
      
      if(loanedTo == null)
      {
         bw.write("null"+'\n');                 
         bw.write("");
      }
      else
      {
         bw.write(loanedTo+'\n');
         bw.write(""+dueDate.getYear() +'\n'
         + dueDate.getMonthValue()+'\n'
         + dueDate.getDayOfMonth()+'\n');
      }
   }

 /**
   * Recors users name and sets/records the due date
   * for publication being check out.
   * 
   * @param patron    the identity of the person borrowing this publication
   * @since              1.0
   */
   public void checkOut(String patron)
   {
      this.loanedTo = patron;
      LocalDate adding = LocalDate.now();
      this.dueDate = adding.plusDays(14);  
   }
   
  protected String toStringBuilder(String pre, String mid) /*verifies if it's a Video or Book*/
  {
     StringBuilder version = new StringBuilder(pre);/* where 'pre': saves "Book" or "Video"*/
                                                   /*and 'mid': saves the run time if an input was given */
     version.append(""+title+" by "+author+" Copyright© "+copyright+ mid+"");
     
     if(loanedTo != null ) /* Also does us a favor to check,"what did user checked out"*/
     {
        version.append(""+":Checked out by: "+loanedTo+ " until " +dueDate+"\n");
        return version.toString();
     }
     else
     {
        return version.toString();
     }
  }

   /**
     * Send a [book] publication to be formatted.
     * NOTE: Clever way we figured out, Since were saving a book without a runtime.
     * Which is meant for only video runtime, but method toStringbuilder requires a string
     * Just save an empty string or better yet another \n!
     * 
     * @returns     the string representation of the publication
     * @since              1.0
     */
   @Override
   public String toString()
   {
      return toStringBuilder("Book:","\n");
   }
}