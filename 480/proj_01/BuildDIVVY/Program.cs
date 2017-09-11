//
// Console app to build a DIVVY database
//
// <<YOUR NAME HERE>>
// U. of Illinois, Chicago
// CS480, Summer 2016
// HW #2
//


using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data.SqlClient;

namespace BuildDIVVY
{
  class Program
  {

    /// <summary>
    /// Makes a copy of an existing Microsoft SQL Server database file 
    /// and log file.  Throws an exception if an error occurs, otherwise
    /// returns normally upon successful copying.  Assumes files are in
    /// sub-folder bin\Debug or bin\Release --- i.e. same folder as .exe.
    /// </summary>
    /// <param name="from">base file name to copy from</param>
    /// <param name="to">base file name to copy to</param>
    static void CopyEmptyFile(string from, string to)
    {
      string from_file, to_file;

      //
      // copy .mdf:
      //
      from_file = from + ".mdf";
      to_file = to + ".mdf";

      if (System.IO.File.Exists(to_file))
      {
        System.IO.File.Delete(to_file);
      }

      System.IO.File.Copy(from_file, to_file);

      // 
      // now copy .ldf:
      //
      from_file = from + "_log.ldf";
      to_file = to + "_log.ldf";

      if (System.IO.File.Exists(to_file))
      {
        System.IO.File.Delete(to_file);
      }

      System.IO.File.Copy(from_file, to_file);
    }


    /// <summary>
    /// Executes the given SQL string, which should be an "action" such as 
    /// create table, drop table, insert, update, or delete.  Returns 
    /// normally if successful, throws an exception if not.
    /// </summary>
    /// <param name="sql">query to execute</param>
    static void ExecuteActionQuery(SqlConnection db, string sql)
    {
      SqlCommand cmd = new SqlCommand();
      cmd.Connection = db;
      cmd.CommandText = sql;

      cmd.ExecuteNonQuery();
    }

    static void Main(string[] args)
    {
      Console.WriteLine();
      Console.WriteLine("** Build DIVVY Database Console App **");
      Console.WriteLine();

      string connectionInfo = String.Format(@"Data Source=(LocalDB)\MSSQLLocalDB;AttachDbFilename=|DataDirectory|\DIVVY.mdf;Integrated Security=True;");
      var db = new SqlConnection(connectionInfo);

      string sql;

      try
      {
        //
        // 1. Make a copy of empty MDF file to get us started:
        //
        Console.WriteLine("Copying empty database file...");

        CopyEmptyFile("__EmptyDB", "DIVVY");

        //
        // 2. Now open DB:
        //
        Console.Write("Opening database connection: ");

        db.Open();

        Console.WriteLine(db.State);

        //
        // 3. Create tables:
        //

        Console.WriteLine("Creating tables...");

        sql = string.Format(@"
CREATE TABLE Customers (
   CustID       INT IDENTITY(1001,1) PRIMARY KEY,
   FirstName    NVARCHAR(64) NOT NULL,         
   LastName     NVARCHAR(64) NOT NULL,
   Email        NVARCHAR(128) NOT NULL,
   DateJoined   DATE NOT NULL
);
");

        ExecuteActionQuery(db, sql);

        //
        // 4. Insert data:
        //
        Console.WriteLine("Inserting data...");

        sql = string.Format(@"
INSERT INTO 
  Customers(FirstName, LastName, Email, DateJoined)
  Values('Joe', 'Hummel', 'jhummel2@uic.edu', GetDate());
");

        ExecuteActionQuery(db, sql);

        //
        // Done
        //
      }
      catch (Exception ex)
      {
        Console.WriteLine("**Exception: '{0}'", ex.Message);
      }
      finally
      {
        Console.Write("Closing database connection: ");

        db.Close();

        Console.WriteLine(db.State);
      }

      Console.WriteLine();
      Console.WriteLine("** Done **");
      Console.WriteLine();
    }//Main

  }//class
}//namespace
