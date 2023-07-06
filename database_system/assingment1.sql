select name
from Pokemon
where type = 'Grass'
order by name asc;

select name
from Trainer
where hometown = 'Brown City' or hometown = 'Rainbow City'
order by name asc;

select distinct type
from Pokemon
order by type asc;

select name
from City
where name like 'B%'
order by name asc;

select hometown
from Trainer
where name not like 'M%'
order by hometown asc;

select nickname
from CatchedPokemon
where level in 
(select max(level)
from catchedpokemon);

select name
from pokemon
where name like 'A%' or name like 'E%' or name like 'I%' or name like 'O%' or  name like'U%'
order by name asc;

select avg(level)
from catchedpokemon;

select max(level)
from catchedpokemon
where owner_id = '5';

select distinct hometown
from trainer
order by hometown asc;

select trainer.name, nickname
from trainer, catchedpokemon
where trainer.id = owner_id and nickname in(
select nickname
from catchedpokemon
where nickname like 'A%')
order by name asc;

select trainer.name
from trainer, gym
where id = leader_id and leader_id in(
select leader_id
from City, gym
where description = 'Amazon' and city = name);

select trainer.id, count(pid) as countFire
from trainer, catchedpokemon
where trainer.id = owner_id and pid in(
select pid
from pokemon, catchedpokemon
where type = 'Fire'and pid = pokemon.id);

select distinct type
from pokemon
where id like '_'
order by id asc;

select count(type)
from pokemon
where type not like 'Fire';

select name
from evolution, pokemon
where before_id > after_id and id = before_id
order by name asc;

select avg(level)
from pokemon, catchedpokemon
where type = 'Water'and pid = pokemon.id;

select nickname
from catchedpokemon
where level in(
select max(level)
from gym,catchedpokemon
where catchedpokemon.owner_id = gym.leader_id);

with avglevel(avg_level,owner_id) as
(select avg(level) as avg_level, owner_id
from trainer, catchedpokemon
where hometown='Blue City' and owner_id = trainer.id
group by owner_id)
select name
from avglevel, trainer
where trainer.id = owner_id and avg_level in (
select max(avg_level)
from avglevel)
order by name asc;

with trainer_id(id) as (
select id
from trainer
group by hometown
having count(hometown) =1)
select pokemon.name
from pokemon, trainer_id, evolution, catchedpokemon
where owner_id = trainer_id.id and pid = evolution.before_id and pokemon.type = 'Electric' and pid = pokemon.id;

select trainer.name, sum(level) as sumlevel
from trainer,gym,catchedpokemon
where trainer.id = leader_id and owner_id=trainer.id
group by owner_id
order by sumlevel asc;

select max(hometown)
from trainer;

with catch(hometown,trainer_id,pid,name) as(
select hometown, trainer.id, pid, pokemon.name
from trainer, catchedpokemon, pokemon
where owner_id = trainer.id and pokemon.id =pid)
select distinct c1.name
from catch c1 inner join catch c2 on c2.name = c1.name and c2.hometown="Sangnok City"
where c1.hometown = 'Brown City'
order by name asc;

with catch(hometown,tname,tid,pid,pname) as(
select hometown,trainer.name, trainer.id, pid, pokemon.name
from trainer, catchedpokemon, pokemon
where owner_id = trainer.id and pokemon.id =pid)
select tname
from catch
where hometown = 'Sangnok City' and pname like 'P%'
order by tname asc;

with catch(hometown,tname,tid,pid,pname) as(
select hometown,trainer.name, trainer.id, pid, pokemon.name
from trainer, catchedpokemon, pokemon
where owner_id = trainer.id and pokemon.id =pid)
select tname, pname
from catch
order by tname, pname asc;

select name
from evolution, pokemon
where id = before_id and before_id not in(
select e1.before_id
from evolution e1, evolution e2
where e1.after_id = e2.before_id or e1.before_id = e2.after_id)
order by name asc;

select nickname
from gym,pokemon,catchedpokemon
where city = "Sangnok City" and type = 'Water' and owner_id = leader_id and pid = pokemon.id
order by nickname asc;

with catch(hometown,tname,tid,pid,pname) as(
select hometown,trainer.name, trainer.id, pid, pokemon.name
from trainer, catchedpokemon, pokemon
where owner_id = trainer.id and pokemon.id =pid)
select tname
from catch, evolution e
where catch.pid = e.after_id
group by tid
having count(pid) > 2
order by tname asc;

select name
from pokemon p
where p.id not in(
select pid
from pokemon, catchedpokemon
where pokemon.id = catchedpokemon.pid)
order by name asc;

select max(level) as maxlevel
from trainer, catchedpokemon
where owner_id = trainer.id
group by hometown
order by maxlevel asc;

with thirdEvolutionID(bid, aid) as (
select e1.before_id, e1.after_id
from evolution e1, evolution e2
where e1.after_id = e2.before_id or e1.before_id = e2.after_id),
thirdEvolutionName(fid,sid,tid) as(
select t1.bid, t2.bid, t2.aid
from thirdEvolutionID t1, thirdEvolutionID t2
where t1.aid = t2.bid and t2.bid= t1.aid)
select t.fid, p1.name, p2.name, p3.name
from pokemon p1, pokemon p2, pokemon p3, thirdEvolutionName t
where p1.id = t.fid and p2.id = t.sid and p3.id = t.tid
order by t.fid asc;
