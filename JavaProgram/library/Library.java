// Copyright 2023 Wilmer Soriano
// This file is part of the Library Management System and is licensed
// under the terms of the Gnu General Public License version 3 or
// any later version, see <https://www.gnu.org/licenses/>.

package library;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.util.ArrayList;

 /**
   * The Library simulation and list of publications
   * Check in/out user
   * and add new publications (Video/Book)
   *
   * @author             Wilmer Soriano
   * @version            1.0
   * @since              1.0
   * @license.agreement  Gnu General Public License 3.0
   */
public class Library
{
   private String name;
   private ArrayList<Publication> publications;

 /**
   *  Store and creates list of storage.
   *
   * basically makes a new array space 
   * available for publication summited
   * @since              1.0
   */
   public Library(String name)
   {
      this.name = name;
      this.publications = new ArrayList<>();
   }

 /**
   * Creates a Library instance from a BufferedReader.
   *
   * See {@link #save(BufferedWriter)} for the expected data format.
   *
   * @param br     a stream positioned where {@link #save(BufferedWriter)} wrote
   * @since        1.2
   */
   public Library(BufferedReader br)throws IOException
   {
      this.name = br.readLine();
      int size  = Integer.parseInt(br.readLine());
      this.publications = new ArrayList<>();

      while(size --> 0)                       
      {
         if(br.readLine().equals("video"))
         {
            publications.add(new Video(br));      //inside of the new array go to either publication or video
         }
         else
         {
            publications.add(new Publication(br));//its not a new book or video but getting out the old data and saving it into a new array.
         }
      }
   }
   
 /**
   * Saves all local fields to the BufferedWriter stream.
   *
   * The value of plain fields that are never null are written one per line. 
   * Lists are written first as the number of elements on a separate line,
   * followed by each element on separate lines (some elements may themselves
   * be multi-line).
   *
   * @param bw    the stream to which all fields will be written
   * @since      1.2
   */
   public void save(BufferedWriter bw)throws IOException
   {
      int size = publications.size();
      bw.write(name + '\n');
      bw.write(""+ size + '\n');
      
      for(var num : publications)  //Save each Publication into Publication
      {
         if(num instanceof Video)
         {
            bw.write("video"+'\n');
         }
         else
         {
            bw.write("publication"+'\n');
         }
         num.save(bw);
      }
   }

 /**
   * add the object into list
   *
   * In terms: adds the book publication
   * 
   * @since              1.0
   */
   public void addPublication(Publication publication){this.publications.add(publication);} 

 /**
   * save user input and name
   * and create a publication function and store the index value 
   * from user.
   * Then heads to checkOut and store user name, found in Publication file, AGAIN NOT IN THIS FILE, ANOTHER ONE FILE!!!
   * @since              1.0
   */
   public void checkOut(int publicationIndex, String patron)
   {
      /*NOTE: it's possible to do this instead--->       publications.get(publicationIndex).checkOut(patron); ALSO, no throw Exce- required*/
      
      Publication Librarian = publications.get(publicationIndex); //Bookmarking The location of the library with Patron name 
      
      Librarian.checkOut(patron);
   }
   
 /**
   * Checks in a publication from this library instance.
   *
   * @param publicationIndex  the index as shown by toString()
   * @since                   1.1
   */
   public void checkIn(int publicationIndex)
   {
      Publication Librarian = publications.get(publicationIndex);
      Librarian.checkOut(null);
   }

 /**
   *  prints out the list saved
   *
   * @UPDATE this file to be able to handle toStringBuild
   * 
   * @since              1.0
   */
   @Override
   public String toString() 
   {
      int x = 0;
      StringBuilder list = new StringBuilder();
      
      list.append("\n\nBookshelf Option:\n\n"); //added the subtitle
      
      while(x < publications.size()) //makes the list of book/video inside of publications
      {
         list.append("" + x + ".)" + publications.get(x)+"\n");
         x++;
      }
      
      return list.toString();   //goes from StringBuilder to now a toString
   }  
}