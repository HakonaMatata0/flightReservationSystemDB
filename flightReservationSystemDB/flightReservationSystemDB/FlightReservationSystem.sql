/*==============================================================*/
/* DBMS name:      Microsoft SQL Server 2005                    */
/* Created on:     5/20/2023 12:00:20 AM                        */
/*==============================================================*/

create database FlightReservationSystem


/*==============================================================*/
/* Table: ADMIN                                                 */
/*==============================================================*/
create table ADMIN (
   ADMIN_ID             varchar(50)          not null,
   FNAME                varchar(20)          not null,
   MNAME                varchar(20)          not null,
   LNAME                varchar(20)          not null,
   EMAIL                varchar(50)          not null,
   constraint PK_ADMIN primary key nonclustered (ADMIN_ID)
)


/*==============================================================*/
/* Table: AIRCRAFT                                              */
/*==============================================================*/
create table AIRCRAFT (
   SERIAL_NUM           varchar(100)         not null,
   ADMIN_ID             varchar(50)          not null,
   MODEL                varchar(100)         not null,
   SEATS_NUM            int                  not null,
   STATUS               bit                  not null,
   constraint PK_AIRCRAFT primary key nonclustered (SERIAL_NUM)
)

/*==============================================================*/
/* Table: AIRPORT                                               */
/*==============================================================*/
create table AIRPORT (
   AIRPORT_ID           varchar(100)         not null,
   ADMIN_ID             varchar(50)          not null,
   AIRPORT_NAME         varchar(100)         not null,
   constraint PK_AIRPORT primary key nonclustered (AIRPORT_ID)
)

/*==============================================================*/
/* Table: BOOKED_FLIGHTS                                        */
/*==============================================================*/
create table BOOKED_FLIGHTS (
   NATIONAL_ID          varchar(50)          not null,
   FLIGHT_ID            int                  not null,
   constraint PK_BOOKED_FLIGHTS primary key (NATIONAL_ID, FLIGHT_ID)
)

/*==============================================================*/
/* Table: FLIGHT                                                */
/*==============================================================*/
create table FLIGHT (
   FLIGHT_ID            int                  not null,
   ADMIN_ID             varchar(50)          not null,
   SERIAL_NUM           varchar(100)         not null,
   AIRPORT_ID           varchar(100)         not null,
   BOOKED_SEATS_NUM     int                  not null,
   REQ_SEATS_NUM        int                  not null,
   SOURCE               varchar(50)          not null,
   DESTINATION          varchar(50)          not null,
   STATUS               bit                  not null,
   DEPATURE_DATE        datetime             not null,
   ARRIVAL_DATE         datetime             not null,
   PRICE                int                  not null,
   FLIGHT_CLASS         varchar(50)          not null,
   constraint PK_FLIGHT primary key nonclustered (FLIGHT_ID)
)

/*==============================================================*/
/* Table: TICKET                                                */
/*==============================================================*/
create table TICKET (
   TICKET_ID            varchar(50)          not null,
   NATIONAL_ID          varchar(50)          not null,
   FLIGHT_ID            int                  not null,
   SEAT_NUM             int                  not null,
   constraint PK_TICKET primary key nonclustered (TICKET_ID)
)


/*==============================================================*/
/* Table: "USER"                                                */
/*==============================================================*/
create table CUSTOMER (
   NATIONAL_ID          varchar(50)          not null,
   CREDITCARD_NUM       varchar(50)          not null,
   EMAIL                varchar(50)          not null,
   PASSWORD             varchar(50)          not null,
   FNAME                varchar(20)          not null,
   MNAME                varchar(20)          not null,
   LNAME                varchar(20)          not null,
   PHONE_NUMBER         varchar(20)          not null,
   constraint PK_USER primary key nonclustered (NATIONAL_ID)
)





alter table AIRCRAFT
   add constraint FK_AIRCRAFT_ENROLL_ADMIN foreign key (ADMIN_ID)
      references ADMIN (ADMIN_ID)


alter table AIRPORT
   add constraint FK_AIRPORT_REGISTER_ADMIN foreign key (ADMIN_ID)
      references ADMIN (ADMIN_ID)


alter table BOOKED_FLIGHTS
   add constraint FK_BOOKED_F_HAS_USER foreign key (NATIONAL_ID)
      references CUSTOMER (NATIONAL_ID)


alter table BOOKED_FLIGHTS
   add constraint FK_BOOKED_F_HAS2_FLIGHT foreign key (FLIGHT_ID)
      references FLIGHT (FLIGHT_ID)


alter table FLIGHT
   add constraint FK_FLIGHT_BELONG_TO_AIRPORT foreign key (AIRPORT_ID)
      references AIRPORT (AIRPORT_ID)


alter table FLIGHT
   add constraint FK_FLIGHT_FLY_BY_AIRCRAFT foreign key (SERIAL_NUM)
      references AIRCRAFT (SERIAL_NUM)


alter table FLIGHT
   add constraint FK_FLIGHT_REGIST_ADMIN foreign key (ADMIN_ID)
      references ADMIN (ADMIN_ID)


alter table TICKET
   add constraint FK_TICKET_BOOK_USER foreign key (NATIONAL_ID)
      references CUSTOMER (NATIONAL_ID)


alter table TICKET
   add constraint FK_TICKET_BOOKED_FL_FLIGHT foreign key (FLIGHT_ID)
      references FLIGHT (FLIGHT_ID)


delete from ticket
delete from flight
delete from Airport
delete from Aircraft
delete from Customer
delete from admin

select * from flight
select * from CUSTOMER
select *from ticket
select * from BOOKED_FLIGHTS