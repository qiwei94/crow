#include "crow.h"
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include "stdint.h"
//#include <string>
int main(){
    crow::SimpleApp app;
    /**
     * the hello world page
     */
    CROW_ROUTE(app,"/hello")
    ([](){
        return "kiwi hello";
    });

    /**
     * 只有一个string作为结果的模板
     */
    CROW_ROUTE(app, "/add_json").methods("POST"_method)
    ([](const crow::request &req) {
            auto x = crow::json::load(req.body);
            if (!x)
                return crow::response(400);
            CROW_LOG_INFO << "OK GET A JSON";
            int sum = x["a"].i() + x["b"].i();
            
            std::ostringstream os;
            os << sum;
            return crow::response{os.str()};
        });
    

    /**
     * get 返回一个json
     */
    CROW_ROUTE(app, "/r_j")
    ([]() {
        crow::json::wvalue x;
        x["first"]=1;
        x["second"]=2;
        return x;
    });

    /**
     * 传入一个json 返回一个json
     */
    CROW_ROUTE(app, "/return_result").methods("POST"_method)
    ([](const crow::request &req) {
        auto x = crow::json::load(req.body);
        crow::json::wvalue y;
        if (!x){
            y["res"]=0;
            return y;
        }
        CROW_LOG_INFO << "OK GET A JSON";
        int sum = x["a"].i() + x["b"].i();

        y["res"]=sum;
        CROW_LOG_INFO << "return a json";
        return y;
    });

    /**
     * add the flow table
    */
    CROW_ROUTE(app, "/add_flow").methods("POST"_method)
    ([](const crow::request &req) {
        auto x = crow::json::load(req.body);
        crow::json::wvalue y;
        if (!x)
        {
            y["res"] = 0;
            return y;
        }
        CROW_LOG_INFO << "OK GET A JSON";
        int32_t request_id = x["request_id"].i();
        uint64_t dev_id = strtoull(x["dev_id"],NULL,0);
        if(AddTableEntry(request_id,dev_id)){
            y["res"] = true;
            CROW_LOG_INFO << "return true";
            return y;
        }else{
            y["res"] = false;
            CROW_LOG_INFO << "return false";
            return y;
        }
    });
    
    /**
     * WritePassiveMeasurementTask
     
    CROW_ROUTE(app, "/write_task").methods("POST"_method)
    ([](const crow::request &req) {
        auto x = crow::json::load(req.body);
        crow::json::wvalue y;
        if (!x)
        {
            y["res"] = 0;
            return y;
        }
        CROW_LOG_INFO << "OK GET A JSON";
        int32_t request_id = x["request_id"].i();
        uint64_t dev_id = strtoull(x["dev_id"], NULL, 0);
        string type = x["type"];
        string filter_type = x["filter_type"];
        uint32_t reportinterval=strtoul(x["reportinterval"],NULL,10);
        uint32_t memorylimitationkb = strtoul(x["memorylimitationkb"],NULL,10);

        int32_t task_id = WritePassiveMeasurementTask(request_id, dev_id, type, filter_type, reportinterval, memorylimitationkb));
        y["task_id"] = task_id;
        CROW_LOG_INFO << "return true";
        return y;
        
    });
    */
    /**
     * read passive res
     
    CROW_ROUTE(app, "/read_passive_result")
    ([]() {
        crow::json::wvalue x;
        
        x["counter"] = 1;
        x["heavey_heater"] = 2;
        return x;
    });
    
    CROW_ROUTE(app, "/delete_passive_task").methods("POST"_method)
    ([](const crow::request &req) {
        auto x = crow::json::load(req.body);
        crow::json::wvalue y;
        if (!x)
        {
            y["res"] = 0;
            return y;
        }
        CROW_LOG_INFO << "OK GET A JSON";
        int task_id = x["task_id"].i();
        uint64_t dev_id = strtoull(x["dev_id"], NULL, 0);
        if (RemovePassiveMeasurementTask(task_id，dev_id)){
            y["res"] = true;
            CROW_LOG_INFO << "delete success";
            return y;
        }else{
            y["res"] = false;
            CROW_LOG_INFO << "delete failure";
            return y;
        }
    });
    */
    app.port(10086).run();
}