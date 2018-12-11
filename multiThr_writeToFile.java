package com.citi.gmd.client.example;

import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import com.citi.gmd.client.book.GMDAbstractBook;
import com.citi.gmd.client.callbacks.GMDComponentCallback;
import com.citi.gmd.client.messages.admin.GMDAdminRespMsg;
import com.citi.gmd.client.messages.component.GMDAbstractMsg;
import com.citi.gmd.client.messages.component.GMDBasketQuoteMsg;
import com.citi.gmd.client.messages.component.GMDCacheClearMsg;
import com.citi.gmd.client.messages.component.GMDClosingTradeSummaryMsg;
import com.citi.gmd.client.messages.component.GMDEnhancedQuoteMsg;
import com.citi.gmd.client.messages.component.GMDFXSnapshotMsg;
import com.citi.gmd.client.messages.component.GMDFeedCfgInfoMsg;
import com.citi.gmd.client.messages.component.GMDFeedStatusMsg;
import com.citi.gmd.client.messages.component.GMDImbalanceMsg;
import com.citi.gmd.client.messages.component.GMDInstrumentStatusMsg;
import com.citi.gmd.client.messages.component.GMDLULDBandMsg;
import com.citi.gmd.client.messages.component.GMDLogOffRespMsg;
import com.citi.gmd.client.messages.component.GMDLogOnRejMsg;
import com.citi.gmd.client.messages.component.GMDLogOnRespMsg;
import com.citi.gmd.client.messages.component.GMDMktStatusMsg;
import com.citi.gmd.client.messages.component.GMDPassThruMsg;
import com.citi.gmd.client.messages.component.GMDPeggedOrderMsg;
import com.citi.gmd.client.messages.component.GMDQuoteMsg;
import com.citi.gmd.client.messages.component.GMDSnpshotCompleteNotification;
import com.citi.gmd.client.messages.component.GMDStaticInfoMsg;
import com.citi.gmd.client.messages.component.GMDSubRespMsg;
import com.citi.gmd.client.messages.component.GMDTheoreticalFillRespMsg;
import com.citi.gmd.client.messages.component.GMDTradeMsg;
import com.citi.gmd.client.messages.component.GMDTradeMsgDetailed;
import com.citi.gmd.client.messages.component.GMDUnSubRespMsg;
import com.citi.gmd.client.utils.structs.CString;
import com.google.gson.Gson;
import com.google.gson.GsonBuilder;
import com.google.gson.TypeAdapter;
import com.google.gson.stream.JsonReader;
import com.google.gson.stream.JsonToken;
import com.google.gson.stream.JsonWriter;

public class GMDExampleJSONWriterComponentCallback extends GMDComponentCallback {
	private static Logger log = LoggerFactory.getLogger(GMDExampleJSONWriterComponentCallback.class);
	private static ArrayList<GMDAbstractMsg> msgList=new ArrayList<GMDAbstractMsg>();
	private static String filename="";
	private static Object locker = new Object();
	private static PrintWriter writer;
	private GMDJsonWriter jsonWriter;
	private static boolean started=false;
	public GMDExampleJSONWriterComponentCallback() {
		Date date = new Date();
        SimpleDateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd-HH-mm-ss");
        filename = ("GMDClientAPI_Json_" + dateFormat.format(date) + ".json");
		try {
			writer = new PrintWriter(new FileWriter(filename));
		} catch (IOException e) {
			log.error("IOException while initializing file",e);
			//e.printStackTrace();
		}
		started=true;
		this.jsonWriter=new GMDJsonWriter();
	}
	
	
    @Override
    public void handleQuoteMsg(GMDQuoteMsg quoteMsg) {
       log.info(quoteMsg.toString());
       msgList.add(quoteMsg);
       notifyJsonWriter();
    }

	@Override
	public void handleTradeMsg(GMDTradeMsg tradeMsg) {
		log.info(tradeMsg.toString());
	}

	@Override
	public void handleImbalanceMsg(GMDImbalanceMsg imbalanceMsg) {
		log.info(imbalanceMsg.toString());
	}

	@Override
	public void handleCacheClearMsg(GMDCacheClearMsg cacheClearMsg) {
		log.info(cacheClearMsg.toString());
	}

	@Override
	public void handleStaticInfoMsg(GMDStaticInfoMsg staticInfoMsg) {
		log.info(staticInfoMsg.toString());
	}

	@Override
	public void handleMarketStatusMsg(GMDMktStatusMsg mktStatusMsg) {
		log.info(mktStatusMsg.toString());
	}

	@Override
	public void handleInstrumentStatusMsg(GMDInstrumentStatusMsg instrumentStatusMsg) {
		log.info(instrumentStatusMsg.toString());
	}

	@Override
	public void handleDetailedTradeMsg(GMDTradeMsgDetailed tradeMsgDetailed) {
		log.info(tradeMsgDetailed.toString());
	}

	@Override
	public void handlePeggedOrderMsg(GMDPeggedOrderMsg peggedOrderMsg) {
		log.info(peggedOrderMsg.toString());
	}

	@Override
	public void handleLogonRej(GMDLogOnRejMsg logOnRejMsg) {
		log.info(logOnRejMsg.toString());
	}

	@Override
	public void handleSubRespMsg(GMDSubRespMsg subRespMsg) {
		log.info(subRespMsg.toString());
	}

	@Override
	public void handleUnSubRespMsg(GMDUnSubRespMsg unSubRespMsg) {
		log.info(unSubRespMsg.toString());
	}

	@Override
	public void handleLogOnRespMsg(GMDLogOnRespMsg logOnRespMsg) {
		log.info(logOnRespMsg.toString());
	}

	@Override
	public void handleLogOffRespMsg(GMDLogOffRespMsg logOffRespMsg) {
		log.info(logOffRespMsg.toString());
	}

	@Override
	public void handleAdminRespMsg(GMDAdminRespMsg adminRespMsg) {
		log.info(adminRespMsg.toString());
	}

	@Override
	public void handleFeedStatusMsg(GMDFeedStatusMsg feedStatusMsg) {
		log.info(feedStatusMsg.toString());
	}

	@Override
	public void handleFeedCfgInfoMsg(GMDFeedCfgInfoMsg fedCfgInfoMsg) {
		log.info(fedCfgInfoMsg.toString());
		
	}

    @Override
    public void handleBasketQuoteMsg(GMDBasketQuoteMsg basketQuoteMsg) {
        log.info(basketQuoteMsg.toString());
    }
    
    @Override
    public void handlePassThruMsg(GMDPassThruMsg passThruMsg) {
        log.info(passThruMsg.toString());
    }
    
    @Override
    public void handleSnapshotCompleteMsg(GMDSnpshotCompleteNotification snpshotComplete) {
        log.info(snpshotComplete.toString());
    }
    
    @Override
    public void handleEnhancedQuoteMsg(GMDEnhancedQuoteMsg enhancedQuoteMsg) {
        log.info(enhancedQuoteMsg.getMsgHdr().toString());
        log.info(enhancedQuoteMsg.toString());        
    }
    
    @Override
    public void handleClosingTradeSummaryMsg(GMDClosingTradeSummaryMsg closingTradeSummaryMsg) {
        log.info(closingTradeSummaryMsg.toString());
    }
    
    @Override
    public void handleLULDBandMsg(GMDLULDBandMsg luldBandMsg) {
        log.info(luldBandMsg.toString());
    }
    
    @Override
    public void handleTheoreticalFillRespMsg(GMDTheoreticalFillRespMsg theoreticalFillRespMsg) {
        log.info(theoreticalFillRespMsg.toString());
    }
    
    @Override
    public void handleFXSnapshotMsg(GMDFXSnapshotMsg fxSnapShotMsg) {
        log.info(fxSnapShotMsg.toString());
    }
    
   
    @Override
    public void handleBookUpdate(GMDAbstractBook book) {
        log.info(book.getSymbol().toString());
        log.info("Buy ");
        while(book.hasMorePriceLevelBuy()){
            log.info(book.getNextPriceLevelBuy().toString());
        }
        log.info("Sell ");
        while(book.hasMorePriceLevelSell()){
            log.info(book.getNextPriceLevelSell().toString());
        }        
    }
    
    private void notifyJsonWriter(){
    	synchronized(locker){
     	   locker.notifyAll();
        }
    }
    
    static class GMDJsonWriter implements Runnable {
		String name;// name of thread
		Thread t;		
		// constructor to initialize the thread
		public GMDJsonWriter() {
			name = "GMDJsonWriter";
			t = new Thread(this, name);
			log.info("json writer started");
			t.start(); // call to run() method
		}

		// This is the entry point for thread.
		public void run() {
			synchronized (locker) {
				GsonBuilder builder = new GsonBuilder();
				builder.registerTypeAdapter(CString.class, new CStringAdapter());
				Gson gson = builder.create();
				while(started){
					if(msgList.size()>0){
						
						String jsonStr=gson.toJson(msgList.remove(0))+"\n";
						log.info("Written: "+jsonStr);
						writer.write(jsonStr);	
						writer.flush();
						
					}else{
						try {
							locker.wait();
						} catch (InterruptedException e) {
							// TODO Auto-generated catch block
							e.printStackTrace();
						}
					}
				}
			}
			log.info("closing JSON writer");
		}

	}
    /**
     * This adapter represents the CString buffer and hash as its toString() equivalent
     * @author sk28838
     *
     */
    private static class CStringAdapter extends TypeAdapter<CString>{

    	@Override
		public CString read(JsonReader reader) throws IOException {
			CString result = new CString("");
			reader.beginObject();
			while(reader.hasNext()){
				String name = reader.nextName();
				if(name.equals("CString")){
					String val=reader.nextString();
					result=new CString(val);
				}else{
			         reader.skipValue();
			    }
			}
			reader.endObject();
	        return result;
		}

		@Override
		public void write(JsonWriter writer, CString arg1) throws IOException {
			writer.beginObject();
			writer.name("CString");
			writer.value(arg1.toString());
			writer.endObject();
			
		}
    	
    }
}
