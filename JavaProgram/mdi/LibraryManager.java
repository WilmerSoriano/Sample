package mdi;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.Console;
import java.io.FileReader;
import java.io.FileWriter;
import java.util.Scanner;

import library.Library;
import library.Publication;
import library.Video;

public class LibraryManager
{
   private Library library;
   
   public LibraryManager(Library library)
   {
      this.library = library;
   }

   public void ShowOptions(String input, String name)
   {
      int num = 0;
      String FileName;
      Scanner user = new Scanner(System.in); 

      switch(input)
      {
         case "0":  //first time welcome
         System.out.println("\nWelcome, "+name+"!\n\n");
         break;

         case "1":  //library
         System.out.println(library);
         break;

         case "2":  //check in
         System.out.println("Checking In:");
         num = Check(num);
         library.checkIn(num);
         System.out.println("\nCheck In Complete!");
         break;

         case "3":  //check out
         System.out.println("Checking Out:");
         num = Check(num);
         library.checkOut(num, name);
         System.out.println("\nCheck Out Complete!");
         break;

         case "4":  //add new book/video.
         publishSomething();
         break;
         
         case "5": //Open Libary
         openLibrary();
         break;
         
         case "6": //Save library 
         saveLibrary();
         break;
         
         default:  //incorrect input
         System.out.println("The following "+ "\""+input+"\""+
         " was not an option try again or press 'x' to EXIT");
      }
   }

   public int Check(int num)
   {
      Scanner scan = new Scanner(System.in);
      System.out.println("\t(choose a book or video found in option 1)");
      System.out.print("\tPress any number found in Bookshelf:");
      num = scan.nextInt();
      return num;
   }

   public void publishSomething()
   {
      String publish;
      String title, author;
      int runtime = 0 ,copyright = 0;
      Console console = System.console();
      Scanner scan = new Scanner(System.in);

      System.out.println("Add the following Information to publish a book or video");

      System.out.println("\nEnter a title: ");
      title = console.readLine();

      System.out.println("Enter an author:");
      author = console.readLine();

      System.out.println("Enter copyright year:");
      copyright = scan.nextInt();

      System.out.println("\nBefore we finish!, What kind of publication is this?");
      System.out.print("(book or video):");
      publish = scan.next();

      if (publish.equals("video"))
      {
         System.out.println("\nEnter runtime (in minutes):");
         runtime = scan.nextInt();
         
         System.out.println("\n\t\tPublishing Video...");

         Video video = new Video(title , author, copyright, runtime);
         library.addPublication(video);
      }
      else 
      {
         System.out.println("\n\t\tPublishing Book...");

         Publication book = new Publication (title, author, copyright);
         library.addPublication(book);
      }
      System.out.println("\t\tPublish Complete!");
   }
   
   public void openLibrary() //This method is implemented with other classes file including the saveLibrary method
   {
      String FileName;
      Console user = System.console();
      System.out.println("Had a previous Library?");
      System.out.print("Enter a filename to open:");
      FileName = user.readLine();
      //next
   
      try(BufferedReader MW = new BufferedReader(new FileReader(FileName))) 
      {
         library = new Library(MW);
      }
      catch(Exception e)
      {
         System.err.println("\nSorry, " + FileName + " file failed to open "+
                                "\n\t\t Exiting Library...");
         System.exit(-2);
      }
   }

   public void saveLibrary()
   {
      String FileName;
      Console user = System.console();

      System.out.println("Save As...");

      System.out.print("Enter a name for File: ");
      FileName = user.readLine();
         
      try(BufferedWriter MW = new BufferedWriter(new FileWriter(FileName)))
      {
         library.save(MW);
      }
      catch(Exception e)
      {
         System.err.println("Sorry, your file "+ FileName + "was unable to be saved"+
                           "\n\t\t Exiting Library...");
         System.exit(-1);
      }
   }
 
   public static void main(String[] args)
   {
      String name;
      String UserInput = "0";
      String libraryName = "The White House Private Library";
      String lines = "\n\t===============================================\n";
      Scanner scan = new Scanner(System.in);

      Library newLibrary = new Library(libraryName);             /*LibraryManager(found in main), encapsulates itself so we can freely*/
      LibraryManager BookShelf = new LibraryManager(newLibrary);/*call methods inside of static main, but first we created a
                                                                new Library (inside of Library folder), so everything is saved in new Library()*/                                         
      BookShelf.Default_Library(); //Deafult hard coded input of book/video.
         
      System.out.print("\nSwip Library Card (enter your name): ");
      name = scan.next();

      while (!UserInput.equals("x"))
      {
         try
         {
            BookShelf.ShowOptions(UserInput, name);
            System.out.print(lines +"\t\t"+libraryName + lines);
            UserInput = BookShelf.LibraryMenu(UserInput);
            System.out.print(lines);
         }
         catch(NumberFormatException e)//... send here to grab that specefic error
         {
            System.err.println("WARNING: Invalid Input, please input Bookshelf number.");
            System.exit(-1);
         }
         catch(Exception e) // This one find any throw(outside of main) and catches it here in main instead
         {
            System.err.println(e.getMessage());
            System.exit(-1);
         }
      }
      System.out.println("Exiting Library ... Have a nice day "+name);
   }

   public void Default_Library()
   {
      Publication book = new Publication ("Overlord", "Kugane Maruyama", 2010); 
      Publication book1 = new Publication ("The Art of War (modern version)", "Sun Tzu", 2005); 
      Publication book2 = new Publication ("The Hunger Games", "Suzanne Collins", 2008); 
         
      Video video3 = new Video("Ender's Game", "Gavin Hood", 2013, 114);
      Video video4 = new Video("Tarzan", "Kevin Lima", 1999, 88);
      Video video5 = new Video("Puss in Boots", "Chris Miller", 2011, 100);
         
      library.addPublication(book);
      library.addPublication(book1); 
      library.addPublication(book2);
         
      library.addPublication(video3);
      library.addPublication(video4);
      library.addPublication(video5);
   }

   public String LibraryMenu(String option)
   {
      Scanner scan = new Scanner(System.in);

      System.out.print("\t\t\t|OPTIONS|:\n\n"+
                        "\t\t\t(press 'x' to EXIT)\n\n"+
                        "\t\t\t1.) print library list\n"+
                        "\t\t\t2.) Check in\n"+
                        "\t\t\t3.) Check out\n"+
                        "\t\t\t4.) add Book/Video\n"+
                        "\t\t\t5.) Open Library\n"+
                        "\t\t\t6.) Save Library\n");
      System.out.print("Enter an option: ");
      option = scan.next();
      return option;
   }
}