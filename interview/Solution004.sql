-- 用户表user: id,name,age; 订单表order: id,user_id,amount,create_time。
-- 需求:查询每个用户的总订单金和和订单数量，结果按照总金额降序排列
select
    u.id,
    u.name,
    sum(o.amount) as total_amount,
    count(o.id) as order_count
from user u
    left join order as o on u.id = o.user_id
group by
    u.id,
    u.name
order by total_amount desc;